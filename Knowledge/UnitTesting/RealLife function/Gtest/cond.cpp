


int   AEVM_EventReport(void){
static int count =0;
count++;
return count;
}
    
       
int error(int value){
    int hi =5;
int VMD_DcVoltage = value;


int  VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS=12;   //12volt
int   VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS=10;  //10volt 
int  VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS=5; //5 volt
int  VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS =7;   //7 volt


int  AEVM_EVENT_REPORT_ST_FAIL=0;
int  AEVM_EVENT_REPORT_ST_PASS=1;
static int last_status_reported_ov =1;
int last_status_reported_uv=1;
 if(VMD_DcVoltage >= VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS)
    {
        /*Update last reported status for DC Over voltage error with FAIL */
        last_status_reported_ov = AEVM_EVENT_REPORT_ST_FAIL;

        /*Report to AEVM status FAIL for DC Over voltage error */
        AEVM_EventReport();
return  last_status_reported_ov;
    }             /*End of if(DCVM_voltage >= DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS) */
   


    else if ((VMD_DcVoltage < VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS) && (VMD_DcVoltage > VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS))
    {
        if (last_status_reported_ov == AEVM_EVENT_REPORT_ST_FAIL)
        {
            /*Report to AEVM status FAIL for DC Over voltage error */
            AEVM_EventReport();
            return  last_status_reported_ov;
        }                                  /*End of if (last_status_reported_ov == AEVM_EVENT_REPORT_ST_FAIL) */
        else
        {
            /*Report to AEVM status PASS for DC Over voltage error */
            AEVM_EventReport();
            return  last_status_reported_ov;
        }/*End of else of if (last_status_reported_ov == AEVM_EVENT_REPORT_ST_FAIL)*/
    }/*End of Else-if*/
   
 
    else/*if (DCVM_voltage <= DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS)*/
    {
        /*Report to AEVM status PASS for DC Over voltage error */
        AEVM_EventReport();
    
        last_status_reported_ov = AEVM_EVENT_REPORT_ST_PASS;
        return  last_status_reported_ov;
     
    }
/*End of else of if(DCVM_voltage >= DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS)*/
    /*UnderVoltage Error Handling*/




    if(VMD_DcVoltage <= VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS)
    {
        /*Update last reported status for DC under voltage error with Fail */
        last_status_reported_uv = AEVM_EVENT_REPORT_ST_FAIL;

        /*Report to AEVM status FAIL for DC under voltage error */
        AEVM_EventReport();
        return  last_status_reported_uv;
    }


    else if ((VMD_DcVoltage > VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS) && (VMD_DcVoltage < VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS))
    {
        if (last_status_reported_uv == AEVM_EVENT_REPORT_ST_FAIL)
        {
            /*Report to AEVM status FAIL for DC under voltage error */
            AEVM_EventReport();
        return  last_status_reported_uv;
        }
        else
        {
            /*Report to AEVM status PASS for DC under voltage error */
            AEVM_EventReport();
            return  last_status_reported_uv;
        }
    }



    else /*if (DCVM_voltage >= DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS)*/
    {
        /*Report to AEVM status PASS for DC under voltage error */
        AEVM_EventReport();
     
        last_status_reported_uv = AEVM_EVENT_REPORT_ST_PASS;
        return  last_status_reported_uv;
     
        /*update "under DC voltage detected" flag at COM signal with False to indicate No under Voltage error exists*/
    }
return hi ;

}



