#include <Arduino.h>

/* FreeRTOS includes */
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include "queue.h"
#include <avr/interrupt.h>


typedef enum
{
    STATE_INIT,
    STATE_IDLE,
    STATE_RUNNING,
    STATE_UPDATE_LED
} SystemState_t;

QueueHandle_t xQueue;
QueueHandle_t xEventQueue;
volatile SystemState_t currentState = STATE_INIT;
TaskHandle_t stateMachineHandle = NULL;




typedef struct
{
    uint8_t type;
    uint8_t value;
} SystemEvent_t;
#define EVENT_LED_UPDATE  1
#define EVENT_LOG         2
#define DATA_PIN 11
#define CLOCK_PIN 13
#define LATCH_PIN 8

void updateShiftRegister(uint8_t data)
{
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data);
    digitalWrite(LATCH_PIN, HIGH);
}

ISR(TIMER1_COMPA_vect)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    vTaskNotifyGiveFromISR(
        stateMachineHandle,
        &xHigherPriorityTaskWoken
    );

    if( xHigherPriorityTaskWoken )
    {
        portYIELD_FROM_ISR();
    }
}



/* Prototype de la tâche */
void vLedTask(void *pvParameters);
void vFastBlinkTask(void *pvParameters);
void vProducerTask(void *pvParameters);
void vConsumerTask(void *pvParameters);
void vEventProducer(void *pvParameters);
void vShiftRegisterTask(void *pvParameters);
void vStateMachineTask(void *pvParameters);
void setupTimer1();


void setup()
{
    xQueue = xQueueCreate(5, sizeof(int));

    xEventQueue = xQueueCreate(10, sizeof(SystemEvent_t));

    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);



    /* Création de la tâche */
        xTaskCreate(
        vLedTask,
        "Heartbeat",
        128,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        vFastBlinkTask,
        "FastBlink",
        128,
        NULL,
        2,
        NULL
    );

    xTaskCreate(vProducerTask, "Producer", 128, NULL, 2, NULL);
    xTaskCreate(vConsumerTask, "Consumer", 128, NULL, 1, NULL);
    xTaskCreate(vEventProducer, "EventProd", 128, NULL, 2, NULL);
    xTaskCreate(vShiftRegisterTask, "ShiftReg", 128, NULL, 2, NULL);
    xTaskCreate(
    vStateMachineTask,
    "StateMachine",
    128,
    NULL,
    2,
    &stateMachineHandle
);

    setupTimer1();


    Serial.begin(9600);

    /* Démarrage du scheduler */
    vTaskStartScheduler();
}

void loop()
{
    
}
void vLedTask(void *pvParameters)
{
    (void) pvParameters;

    pinMode(LED_BUILTIN, OUTPUT);

    for (;;)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));

        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vFastBlinkTask(void *pvParameters)
{
    (void) pvParameters;

    pinMode(LED_BUILTIN, OUTPUT);

    for (;;)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(100));

        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vProducerTask(void *pvParameters)
{
    int counter = 0;

    for(;;)
    {
        counter++;

        xQueueSend(
            xQueue,
            &counter,
            portMAX_DELAY
        );

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vConsumerTask(void *pvParameters)
{
    int receivedValue;

    for(;;)
    {
        if(xQueueReceive(
            xQueue,
            &receivedValue,
            portMAX_DELAY))
        {
            Serial.print("Received: ");
            Serial.println(receivedValue);
        }
    }
}

void vEventProducer(void *pvParameters)
{
    SystemEvent_t event;
    uint8_t counter = 0;

    for(;;)
    {
        counter++;

        event.type = EVENT_LED_UPDATE;
        event.value = counter;

        xQueueSend(xEventQueue, &event, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vShiftRegisterTask(void *pvParameters)
{
    SystemEvent_t event;

    for(;;)
    {
        if(xQueueReceive(xEventQueue, &event, portMAX_DELAY))
        {
            if(event.type == EVENT_LED_UPDATE)
            {
                updateShiftRegister(event.value);
            }
        }
    }
}

void setupTimer1()
{
    cli();

    TCCR1A = 0;
    TCCR1B = 0;

    OCR1A = 15624; // 1 sec @16MHz /1024

    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);

    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void vStateMachineTask(void *pvParameters)
{
    uint8_t ledValue = 0;

    for(;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        switch(currentState)
        {
            case STATE_INIT:
                Serial.println("INIT");
                currentState = STATE_IDLE;
                break;

            case STATE_IDLE:
                currentState = STATE_RUNNING;
                break;

            case STATE_RUNNING:
                ledValue++;
                currentState = STATE_UPDATE_LED;
                break;

            case STATE_UPDATE_LED:
                updateShiftRegister(ledValue);
                currentState = STATE_IDLE;
                break;
        }
    }
}
