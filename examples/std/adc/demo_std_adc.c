/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ADC���̣����ò�ѯ��ʽ��ȡADCת�������ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ָ��ADCͨ����Ӧ����������ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_std_adc.c src_std_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 17-05-05  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_adc
 * \copydoc demo_std_adc.c
 */

/** [src_std_adc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_adc.h"

/**
 * \brief ��ȡ ADC ת��ֵ
 */
static uint32_t __adc_code_get (am_adc_handle_t handle, int chan)
{
    int      adc_bits = am_adc_bits_get(handle, chan);
    int      i;
    uint32_t sum;

    /*
     * ����ADCת�������ɼ�12�� CODE ֵ
     *
     * ʵ��Ӧ���У���ʹ�õ� ADC λ����ȷ���ģ����������ֶ����������
     */
    if (adc_bits <= 8) {
        uint8_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    } else if (adc_bits <= 16) {
        uint16_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    } else {
        uint32_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    }
    return (sum / 12);
}

/**
 * \brief �������
 */
void demo_std_adc_entry (am_adc_handle_t handle, int chan)
{

    int adc_bits = am_adc_bits_get(handle , chan);        /* ��ȡADCת������ */
    int adc_vref = am_adc_vref_get(handle , chan);

    uint32_t adc_code;                                    /* ���� Code ֵ   */
    uint32_t adc_mv;                                      /* ������ѹ */

    am_kprintf("The ADC value channel is %d: \r\n",chan);

    if (adc_bits < 0 || adc_bits >= 32) {
        am_kprintf("The ADC  channel is error, Please check! \r\n");
        return;
    }

    while (1) {

        adc_code = __adc_code_get(handle, chan);
        adc_mv   = adc_code * adc_vref / ((1UL << adc_bits) - 1);

        /* �������������ѹֵ */
        am_kprintf("Sample : %d, Vol: %d mv\r\n", adc_code, adc_mv);

        am_mdelay(500);
    }
}
/** [src_std_adc] */

/* end of file */