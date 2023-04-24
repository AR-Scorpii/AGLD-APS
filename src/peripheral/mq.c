#include "mq.h"

void MQ_Init(void)
{
    ADC_Init();
}

uint32_t MQ_ResistGet(void)
{
    uint16_t adcval = ADC_Sample(ADC_Channel_P04);
#   ifdef _DEBUG
    printf("[MQ] ADC value: %lu\n", adcval);
#   endif

    MDU_Reset();
    // (4096 - adcval) * Rc
    MDU_ValSet(MDU_ValFmt_1to0, 4096ul - adcval);
    MDU_ValSet(MDU_ValFmt_5to4, 51000ul);
    MDU_Calc(MDU_Alg_Mul);
    // ans / adcval
    MDU_ValSet(MDU_ValFmt_5to4, adcval);
    MDU_Calc(MDU_Alg_Div32);

    uint32_t mqr = MDU_ValGet(MDU_ValFmt_3to0);
#   ifdef _DEBUG
    printf("[MQ] sensor resistance: %lu\n", mqr);
#   endif
    return mqr;
}

uint16_t MQ_ConcGet(void)
{
    uint32_t mqr = MQ_ResistGet();

    // mqc = 2.77925e8 * mqr^(-1.38435);
    float tmp = 2.77925e8f * powf(mqr, -1.38435f);
    uint16_t mqc = (uint16_t) tmp;

#   ifdef _DEBUG
    printf("[MQ] gas concentration: %u\n", mqc);
#   endif

    return mqc;
}