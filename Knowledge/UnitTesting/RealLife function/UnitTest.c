//I want to analysis the code to make a unit test for it


void VMD_SlowCycle(void)
{
    /*Declaration for last reported status variables for over/under voltage thresholds */
    static uint8_t  last_status_reported_ov = AEVM_EVENT_REPORT_ST_INIT;
    static uint8_t  last_status_reported_uv = AEVM_EVENT_REPORT_ST_INIT;
    /*local variable for the status of the over voltage */
    static uint8_t ov_status  = VMD_BVMD_ERROR_STATUS_PASS;
    /*local variable for the status of the under voltage */
    static uint8_t uv_status  = VMD_BVMD_ERROR_STATUS_PASS;
    /*local variable for the status of the critical over voltage */
    static uint8_t cov_status = VMD_BVMD_ERROR_STATUS_PASS;
    /*local variable for the status of the critical under voltage */
    static uint8_t cuv_status = VMD_BVMD_ERROR_STATUS_PASS;
#if VMD_LV_MODE == VMD_ENABLE  //if the logic supply voltage is enabled
    /*local variable for the status of the over logic supply voltage */
    static uint16_t AEVM_EventReportSt_logic_supply_OV_STATUS = VMD_BVMD_ERROR_STATUS_PASS;
    /*local variable for the status of the under logic supply voltage */
    static uint16_t AEVM_EventReportSt_logic_supply_UV_STATUS_  = VMD_BVMD_ERROR_STATUS_PASS;
#endif
    /*Define exit loop condition local variable*/
#if CC_VMD_INTERRUPT_VARIANT == VMD_VARI_POLLING_MODE
    uint8_t  breakloop_counter = VMD_DCVM_CFG_MAX_BREAK_LOOP_COUNTER;
    while( (!ADC_HAL_CHANNEL_STATE_GET(VMD_DC_VOLTAGE_CFG_ADC_CH)) && ( --breakloop_counter > 0));
    VMD_DcVoltage_adc_data = ADC_HAL_CHANNEL_READING_GET(VMD_DC_VOLTAGE_CFG_ADC_CH);
    ADC_HAL_CHANNEL_STATE_RESET(VMD_DC_VOLTAGE_CFG_ADC_CH);
#endif /*End of #if CC_DCVM_INTERRUPT_VARIANT == DCVM_VARI_POLLING_MODE*/
    /* Get DC Voltage in volts scaled up by 1024 */
    VMD_DcVoltage = VMD_DCVM_AdcToScaledDCVoltageConvert(VMD_DcVoltage_adc_data);
    #if VMD_LV_MODE == VMD_ENABLE
    vmd_logicVoltage = vmd_bvmd_logic_supply_AdcToScaledVbatVoltsConvert(vmd_avg_adc_logicVoltage_readings);
    uint32_t BVMD_logic_supply_voltage_mV=(uint32_t)(((uint64_t)vmd_logicVoltage * VMD_CFG_RESOLUTION_BITS *VMD_BVMD_MILLI_VOLT_CONVERSION_RATIO)>> VMD_CFG_RESOLUTION_BITS) ;  //FIRST DIVIDE BY 100 then multiply with 100 to take only one digit after point
    #endif


#define VMD_DcVoltage 50;
#define BVMD_logic_supply_voltage_mV 100;

//--------------------------------------------------------------------------------------------------------------------------

    /*OverVoltage Error Handling*/
    if(VMD_DcVoltage >= VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS)
    {
        /*Update last reported status for DC Over voltage error with FAIL */
        last_status_reported_ov = AEVM_EVENT_REPORT_ST_FAIL;
        
        /*Report to AEVM status FAIL for DC Over voltage error */
        AEVM_EventReport(DCVM_ERROR_MEASURED_DC_OVER_VOLTAGE, AEVM_EVENT_REPORT_ST_FAIL);
    }                                   /*End of if(DCVM_voltage >= DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS) */
   
    else if ((VMD_DcVoltage < VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS) && (VMD_DcVoltage > VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS))
    {
        if (last_status_reported_ov == AEVM_EVENT_REPORT_ST_FAIL)
        {
            /*Report to AEVM status FAIL for DC Over voltage error */
            AEVM_EventReport(DCVM_ERROR_MEASURED_DC_OVER_VOLTAGE, AEVM_EVENT_REPORT_ST_FAIL);
        }                                  /*End of if (last_status_reported_ov == AEVM_EVENT_REPORT_ST_FAIL) */
        else
        {
            /*Report to AEVM status PASS for DC Over voltage error */
            AEVM_EventReport(DCVM_ERROR_MEASURED_DC_OVER_VOLTAGE, AEVM_EVENT_REPORT_ST_PASS);
        }/*End of else of if (last_status_reported_ov == AEVM_EVENT_REPORT_ST_FAIL)*/
    }/*End of Else-if*/
    
    else/*if (DCVM_voltage <= DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS)*/
    {
        /*Report to AEVM status PASS for DC Over voltage error */
        AEVM_EventReport(DCVM_ERROR_MEASURED_DC_OVER_VOLTAGE, AEVM_EVENT_REPORT_ST_PASS);
    
        last_status_reported_ov = AEVM_EVENT_REPORT_ST_PASS;
     
    }/*End of else of if(DCVM_voltage >= DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS)*/
    
    

//---------------------------------------------------------------------------------------------------------------------------










    /*UnderVoltage Error Handling*/

    if(VMD_DcVoltage <= VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS)
    {
        /*Update last reported status for DC under voltage error with Fail */
        last_status_reported_uv = AEVM_EVENT_REPORT_ST_FAIL;

        /*Report to AEVM status FAIL for DC under voltage error */
        AEVM_EventReport(DCVM_ERROR_MEASURED_DC_UNDER_VOLTAGE, AEVM_EVENT_REPORT_ST_FAIL);
    }

    else if ((VMD_DcVoltage > VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS) && (VMD_DcVoltage < VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS))
    {
        if (last_status_reported_uv == AEVM_EVENT_REPORT_ST_FAIL)
        {
            /*Report to AEVM status FAIL for DC under voltage error */
            AEVM_EventReport(DCVM_ERROR_MEASURED_DC_UNDER_VOLTAGE, AEVM_EVENT_REPORT_ST_FAIL);
        }
        else
        {
            /*Report to AEVM status PASS for DC under voltage error */
            AEVM_EventReport(DCVM_ERROR_MEASURED_DC_UNDER_VOLTAGE, AEVM_EVENT_REPORT_ST_PASS);
        }
    }

    else /*if (DCVM_voltage >= DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS)*/
    {
        /*Report to AEVM status PASS for DC under voltage error */
        AEVM_EventReport(DCVM_ERROR_MEASURED_DC_UNDER_VOLTAGE, AEVM_EVENT_REPORT_ST_PASS);
     
        last_status_reported_uv = AEVM_EVENT_REPORT_ST_PASS;
     
        /*update "under DC voltage detected" flag at COM signal with False to indicate No under Voltage error exists*/
    }





   //*****************************************************Cancelled***************** 
    #if VMD_LV_MODE == VMD_ENABLE
    /* Check if measured logic supply voltage voltage is equal or higher than maximum logic supply voltage threshold*/
            if(BVMD_logic_supply_voltage_mV >= VMD_BVMD_CFG_RAW_LOGIC_SUPPLY_VOLTAGE_MAXIMUM_THRESHOLD)
            {
                /* logic supply voltage is equal to or exceed maximum threshold*/
                AEVM_EventReportSt_logic_supply_OV_STATUS=VMD_BVMD_ERROR_STATUS_FAIL;
            }/*if(BVMD_logic_supply_voltage_mV >= BVMD_CFG_RAW_LOGIC_SUPPLY_VOLTAGE_MAXIMUM_THRESHOLD)*/
            else
            {
                /*Implement hysteresis*/
                if(BVMD_logic_supply_voltage_mV < VMD_BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD)
                {
                /* Logic supply voltage is lower than maximum overvoltage clear threshold*/
                AEVM_EventReportSt_logic_supply_OV_STATUS=VMD_BVMD_ERROR_STATUS_PASS;
                }/*if((BVMD_logic_supply_voltage_mV <= BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD))*/
                else
                {
                   
                }/*End of if  if((BVMD_logic_supply_voltage_mV < BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD)) */
                   
            } /* End of if(BVMD_logic_supply_voltage_mV >= BVMD_CFG_BATTERY_VOLTAGE_MAXIMUM_THRESHOLD_SCALED) */







        /* Check if measured logic supply voltage  is equal or less than minimum logic supply voltage threshold*/
            if(BVMD_logic_supply_voltage_mV <= VMD_BVMD_CFG_RAW_LOGIC_SUPPLY_VOLTAGE_MINIMUM_THRESHOLD)
            {
                /* logic supply voltage is equal to or below minimum threshold*/
                AEVM_EventReportSt_logic_supply_UV_STATUS_=VMD_BVMD_ERROR_STATUS_FAIL;
            }/*if(BVMD_battery_voltage_mV <= BVMD_CFG_RAW_LOGIC_SUPPLY_VOLTAGE_MINIMUM_THRESHOLD)*/
            else
            {
                /*Implement hysteresis*/
                if(BVMD_logic_supply_voltage_mV >= VMD_BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MINIMUM_CLEAR_THRESHOLD)
                {
                /* Logic supply voltage exceed than minimum overvoltage clear threshold*/
                AEVM_EventReportSt_logic_supply_UV_STATUS_=VMD_BVMD_ERROR_STATUS_PASS;
                }/*if((BVMD_logic_supply_voltage_mV >= BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MINIMUM_CLEAR_THRESHOLD))*/
                else
                {   /*check if the last value before current one pass or fail */
                   
                        
                }/*else of if((BVMD_logic_supply_voltage_mV > BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MINIMUM_CLEAR_THRESHOLD))*/
                
            } /* End of if(BVMD_logic_supply_voltage_mV <= BVMD_CFG_RAW_LOGIC_SUPPLY_VOLTAGE_MINIMUM_THRESHOLD) */
    #endif
//*****************************************************Cancelled***************** 







/**************************************** BATTERY ************************************/
/***********************************************  */


    /* Check if measured battery voltage is equal or higher than maximum battery voltage threshold*/
    if(battery_voltage_mV >=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MAXIMUM_THRESHOLD_MV)
    {
        /*raise flag for that "the  over voltage error is occured"*/
        ov_status=VMD_BVMD_ERROR_STATUS_FAIL;
    }/*if(battery_voltage_mV >= BVMD_CFG_VOLTAGE_MAXIMUM_THRESHOLD_MV)*/
    else
    {
        /*check if the Battery voltage is less than or equal the clear value of the over voltage error */
        if(battery_voltage_mV <=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD_MV )
        {
            /*raise flag for that "the  over voltage error is recovered"*/
            ov_status=VMD_BVMD_ERROR_STATUS_PASS;
        }/*if((battery_voltage_mV <= BVMD_CFG_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD_MV ))*/
        else
        {
                   
        }/*End of if  if((battery_voltage_mV < BVMD_CFG_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD_MV )) */
                   
    } /* End of if(local_battery_voltage_scaled >= BVMD_CFG_VOLTAGE_MAXIMUM_THRESHOLD_MV) */











    /*check if measured battery voltage equal or higher than critical max voltage */
    if(battery_voltage_mV >=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_THRESHOLD_MV )
    {
        /*raise flag for that "the critical over voltage error is occured"*/
        cov_status=VMD_BVMD_ERROR_STATUS_FAIL;
    }/*end of if (battery_voltage_mV >= BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_THRESHOLD_MV )*/
    else 
    {
        /*check if the measured value less than or equal the clear value of the critical over voltage error*/
        if(battery_voltage_mV <=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_CLEAR_THRESHOLD_MV )
        {
            /*raise flag for that "the critical over voltage error is recovered"*/
            cov_status=VMD_BVMD_ERROR_STATUS_PASS;
        }/*end of if battery_voltage_mV <= BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_CLEAR_THRESHOLD_MV */
        else
        {   /*check if the last value before current one pass or fail */
                         
        }/*else for battery_voltage_mV < BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_CLEAR_THRESHOLD_MV */
    }/*else for (battery_voltage_mV >= BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_THRESHOLD_MV */

    /* Check if measured battery voltage is equal or less than minimum battery voltage threshold*/
    if(battery_voltage_mV <=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MINIMUM_THRESHOLD_MV )
    {
        /*raise flag for that "the under voltage error is occured"*/
        uv_status=VMD_BVMD_ERROR_STATUS_FAIL;
    }/*if(battery_voltage_mV <= BVMD_CFG_VOLTAGE_MINIMUM_THRESHOLD_MV )*/
    else
    {
         /*check if the measured value more than or equal the clear value of the under voltage error*/
        if(battery_voltage_mV >=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MINIMUM_CLEAR_THRESHOLD_MV )
        {
            /*raise flag for that "the under voltage error is recovered"*/
            uv_status=VMD_BVMD_ERROR_STATUS_PASS;
        }/*if((battery_voltage_mV >= BVMD_CFG_VOLTAGE_MINIMUM_CLEAR_THRESHOLD_MV ))*/
        else
        {   /*check if the last value before current one pass or fail */
                   
                        
        }/*else of if((battery_voltage_mV > BVMD_CFG_VOLTAGE_MINIMUM_CLEAR_THRESHOLD_MV ))*/
                
    } /* End of if(local_battery_voltage_scaled <= BVMD_CFG_VOLTAGE_MINIMUM_THRESHOLD_MV ) */

    /*check if measured less than critical minimum voltage */
    if(battery_voltage_mV <=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_THRESHOLD_MV )
    {
        /*raise flag for that "the critical under voltage error is occured"*/
        cuv_status=VMD_BVMD_ERROR_STATUS_FAIL;  
    }
    else 
    {
       /*check if the measured value more than or equal the clear value of the critical under voltage error*/
        if(battery_voltage_mV >=(uint16_t) VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_CLEAR_THRESHOLD_MV )
        {
            /*raise flag for that "the critical under voltage error is recovered"*/
            cuv_status=VMD_BVMD_ERROR_STATUS_PASS;
        }/*end if (battery_voltage_mV >= BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_CLEAR_THRESHOLD_MV )*/
        else
        {   /*check if the last value before current one pass or fail */
                        
        }/*else for (battery_voltage_mV > BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_CLEAR_THRESHOLD_MV )*/
    }/*else for battery_voltage_mV <= BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_THRESHOLD_MV */

    /*report to the AEVM the status of the over voltage error*/    
    AEVM_EventReport(BVMD_ERROR_OVERTHRESHOLD, ov_status);
    /*report to the AEVM the status of the critical over voltage error*/  
    AEVM_EventReport(BVMD_ERROR_OVERTHRESHOLD_CRITICAL, cov_status);
    /*report to the AEVM the status of the under voltage error*/  
    AEVM_EventReport(BVMD_ERROR_UNDERTHRESHOLD, uv_status);
    /*report to the AEVM the status of the critical under voltage error*/  
    AEVM_EventReport(BVMD_ERROR_UNDERTHRESHOLD_CRITICAL, cuv_status);
    #if VMD_LV_MODE == VMD_ENABLE
    /*report to the AEVM the status of the over logic supply voltage error*/  
    AEVM_EventReport(BVMD_ERROR_LOGIC_SUPPLY_OVERTHRESHOLD, AEVM_EventReportSt_logic_supply_OV_STATUS);
    /*report to the AEVM the status of the under logic supply voltage error*/  
    AEVM_EventReport(BVMD_ERROR_LOGIC_SUPPLY_UNDERTHRESHOLD, AEVM_EventReportSt_logic_supply_UV_STATUS_);
#endif
}