/*********************************************************************
 * 
 *	Utilities functions
 * 
 *	Author : Sébastien PERREAU
 * 
*********************************************************************/

#include "../PLIB2.h"

/*******************************************************************************
 * Function: 
 *      void fu_switch(switch_params_t *var)
 * 
 * Description:
 *      This routine is used to manage a switch (debounce & type of push included).
 * 
 * Parameters:
 *      *var: The pointer of switch_params_t.
 * 
 * Return:
 *      none
 ******************************************************************************/
void fu_switch(switch_params_t *var)
{
    if (!var->is_initialization_done)
    {
        ports_reset_pin_input(var->io);
        var->is_initialization_done = true;
    }
    else
    {
        bool input_state = var->active_state ? ports_get_bit(var->io) : !ports_get_bit(var->io);
        
        if (input_state)
        {
            if (!var->is_debounce_protection_active)
            {
                var->indice++;
                var->is_updated = true;
                var->type_of_push = SIMPLE_PUSH;
                var->is_debounce_protection_active = true;
                var->tick_longpush = mGetTick();
            }
            else if (mTickCompare(var->tick_longpush) >= TICK_1S)
            {
                var->type_of_push = LONG_PUSH;
            }
            var->tick_debounce = mGetTick();
        }
        else if (mTickCompare(var->tick_debounce) >= TICK_10MS)
        {
            var->is_debounce_protection_active = false;
        }
    }
}

/*******************************************************************************
 * Function: 
 *      void fu_encoder(encoder_params_t *var)
 * 
 * Description:
 *      This routine is used to manage an encoder. You can either use pull_up or 
 *      pull_down resistors on inputs (A & B) but you have to indicate which 
 *      active_state you want to use.
 * 
 * Parameters:
 *      *var: The pointer of encoder_params_t.
 * 
 * Return:
 *      none
 ******************************************************************************/
void fu_encoder(encoder_params_t *var)
{
    if (!var->is_initialization_done)
    {
        ports_reset_pin_input(var->io[0]);
        ports_reset_pin_input(var->io[1]);
        var->is_initialization_done = true;
    }
    else
    {
        bool input_a = var->active_state ? ports_get_bit(var->io[0]) : !ports_get_bit(var->io[0]);
        bool input_b = var->active_state ? ports_get_bit(var->io[1]) : !ports_get_bit(var->io[1]);

        if((var->a0 != input_a) && (var->b0 == input_b))
        {
            var->add = 1;
        }
        else if((var->a0 == input_a) && (var->b0 != input_b))
        {
            var->add = -1;
        }
        else if((var->a0 != input_a) && (var->b0 != input_b))
        {
            var->a0 = input_a;
            var->b0 = input_b;
            var->indice += var->add;
            var->last_direction = var->add;
        }
        else if((var->a0 == input_a) && (var->b0 == input_b))
        {
            var->add = 0;
        }
    }
}

/*******************************************************************************
 * Function: 
 *      bool fu_turn_indicator(bool enable, uint32_t time_on, uint32_t time_off)
 * 
 * Description:
 *      This routine is used to manage a turn indicator function.
 * 
 * Parameters:
 *      enable: enable or disable the function.
 *      time_on: time during state of ti is ON.
 *      time_off: time during state of ti is OFF.
 * 
 * Return:
 *      The current state of the turn indicator. Should be apply to an I/O pin.
 ******************************************************************************/
bool fu_turn_indicator(bool enable, uint32_t time_on, uint32_t time_off)
{
    static uint64_t tick_ti = 0;
    static bool state = 0;

    if(enable)
    {
        if(state)
        {
            if(mTickCompare(tick_ti) >= time_on)
            {
                tick_ti = mGetTick();
                state = 0;
            }
        }
        else
        {
            if(mTickCompare(tick_ti) >= time_off)
            {
                tick_ti = mGetTick();
                state = 1;
            }
        }
    }
    else
    {
        tick_ti = mGetTick();
        state = 0;
    }

    return state;
}

/*******************************************************************************
 * Function: 
 *      void fu_led(led_params_t *var)
 * 
 * Description:
 *      This routine is used for managing a LED (pwm value, time up, time down...).
 * 
 * Parameters:
 *      *var: A pointer of led_params_t.
 * 
 * Return:
 *      none.
 ******************************************************************************/
void fu_led(led_params_t *var)
{    
    if (var->enable)
    {
        if (*var->p_out < var->intensity)
        {
            if (mTickCompare(var->tick) >= var->t_up)
            {
                var->tick = mGetTick();
                (*(var->p_out))++;
            }
        }
        else if (*var->p_out > var->intensity)
        {
            if (mTickCompare(var->tick) >= var->t_down)
            {
                var->tick = mGetTick();
                (*(var->p_out))--;
            }
        }
    }
    else if (mTickCompare(var->tick) >= var->t_down)
    {
        var->tick = mGetTick();
        if (*var->p_out > 0)
        {
            (*(var->p_out))--;
        }
    }
}

/*******************************************************************************
 * Function: 
 *      hsv_color_t fu_rgb_to_hsv(rgb_color_t rgb_color)
 * 
 * Description:
 *      This routine is used to convert a RGB model to a HSV model.
 * 
 * Parameters:
 *      rgb_color: A RGB model.
 * 
 * Return:
 *      A HSV model. 
 ******************************************************************************/
hsv_color_t fu_rgb_to_hsv(rgb_color_t rgb_color)
{
    float min, max, delta, x;
    hsv_color_t hsv_color = {0};
    
    min = (rgb_color.red < rgb_color.green) ? rgb_color.red : rgb_color.green;
    min = (min < rgb_color.blue) ? min : rgb_color.blue;
    max = (rgb_color.red > rgb_color.green) ? rgb_color.red : rgb_color.green;
    max = (max > rgb_color.blue) ? max : rgb_color.blue;
    delta = max - min;
    
    if(max > 0.0)
    {
        if(rgb_color.red >= max)
        {
            x = (255.0 * (rgb_color.green - rgb_color.blue) / delta);
        }
        else if(rgb_color.green >= max)
        {
            x = (510.0 + 255.0 * (rgb_color.blue - rgb_color.red) / delta);
        }
        else
        {
            x = (1020.0 + 255.0 * (rgb_color.red - rgb_color.green) / delta);
        }
        
        hsv_color.hue = (uint16_t) ((x >= 0.0) ? x : (x + 1529.0));
        hsv_color.saturation = (uint8_t) (delta * 255.0 / max);
        hsv_color.value = (uint8_t) max;
    }
    
    return hsv_color;
}

/*******************************************************************************
 * Function: 
 *      rgb_color_t fu_hsv_to_rgb(hsv_color_t hsv_color)
 * 
 * Description:
 *      This routine is used to convert a HSV model to a RGB model.
 * 
 * Parameters:
 *      hsv_color: A HSV model.
 * 
 * Return:
 *      A RGB model. 
 ******************************************************************************/
rgb_color_t fu_hsv_to_rgb(hsv_color_t hsv_color)
{
    uint8_t shade_index;
    rgb_color_t rgb_color = {0};
    
    shade_index = (hsv_color.hue / 255);
    float f = (float) ((hsv_color.hue / 255.0) - shade_index);
    uint16_t l = hsv_color.value * (255 - hsv_color.saturation) / 255;
    uint16_t m = hsv_color.value * (255 - (float) (f * hsv_color.saturation)) / 255;
    uint16_t n = hsv_color.value * (255 - hsv_color.saturation + (float) (f * hsv_color.saturation)) / 255;
    
    switch (shade_index)
    {
        case 0:
            
            rgb_color.red = hsv_color.value;
            rgb_color.green = n;
            rgb_color.blue = l;
            break;
            
        case 1:
            
            rgb_color.red = m;
            rgb_color.green = hsv_color.value;
            rgb_color.blue = l;
            break;
            
        case 2:
            
            rgb_color.red = l;
            rgb_color.green = hsv_color.value;
            rgb_color.blue = n;
            break;
            
        case 3:
            
            rgb_color.red = l;
            rgb_color.green = m;
            rgb_color.blue = hsv_color.value;
            break;
            
        case 4:
            
            rgb_color.red = n;
            rgb_color.green = l;
            rgb_color.blue = hsv_color.value;
            break;
            
        case 5:
            
            rgb_color.red = hsv_color.value;
            rgb_color.green = l;
            rgb_color.blue = m;
            break;
            
        default:
            
            rgb_color.red = 0;
            rgb_color.green = 0;
            rgb_color.blue = 0;
            break;
            
    }
    
    return rgb_color;
}

/*******************************************************************************
 * Function: 
 *      SLIDER_STATUS fu_slider(slider_params_t *var)
 * 
 * Description:
 *      This routine is used to manage a slider object. 
 *      No LED objects are attach to its parameters in order to keep the function
 *      as most "generic" as possible. Thus you can use it anywhere.
 * 
 * Parameters:
 *      *var: The pointer of slider_params_t.
 * 
 * Return:
 *      It returns the status of the slider routine (See. SLIDER_STATUS enumeration).
 ******************************************************************************/
SLIDER_STATUS fu_slider(slider_params_t *var)
{    
    SLIDER_STATUS ret;
    
    if (var->save_state != var->enable)
    {
        var->save_state = var->enable;
        var->p_output.index = 0;
        var->_time = (var->enable ? var->time_on : var->time_off) / var->p_output.size;
        var->_mode = (var->enable ? var->mode_on : var->mode_off);
    }
    
    if (var->p_output.index < var->p_output.size)
    {
        ret = SLIDER_TRANSITION_WAIT;
        if ((var->_mode & 0x0f) == 0)
        {
            var->p_output.p[var->p_output.index++] = var->enable;
            ret = SLIDER_TRANSITION_UPDATE;
        }
        else if (mTickCompare(var->state_machine.tick) >= var->_time)
        {
            var->state_machine.tick = mGetTick();

            if (GET_BIT(var->_mode, 0))
            {
                var->p_output.p[var->p_output.index] = var->enable;
            }
            else if (GET_BIT(var->_mode, 1))
            {
                var->p_output.p[var->p_output.size - 1 - var->p_output.index] = var->enable;
            }
            else if (GET_BIT(var->_mode, 2))
            {                
                var->p_output.p[var->p_output.size/2 + var->p_output.index/2] = var->enable;
                var->p_output.p[var->p_output.size/2 - var->p_output.index/2 - ((var->p_output.size - 1) % 2)] = var->enable;
            }
            else if (GET_BIT(var->_mode, 3))
            {
                var->p_output.p[var->p_output.index/2] = var->enable;
                var->p_output.p[var->p_output.size - 1 - var->p_output.index/2] = var->enable;
            }
            var->p_output.index++;
            ret = SLIDER_TRANSITION_UPDATE;
        }
    }
    else
    {
        ret = SLIDER_SUCCESS;
    }
    
    return ret;
}

/*******************************************************************************
 * Function: 
 *      void fu_adc_average(average_params_t *var)
 * 
 * Description:
 *      This routine is used to get the average of an ADC acquisition.
 * 
 * Parameters:
 *      *var: The pointer of average_params_t.
 * 
 * Return:
 *      true: if new acquisition and new average calculated.
 *      false: if no new acquisition.
 ******************************************************************************/
bool fu_adc_average(average_params_t *var)
{    
    if(mTickCompare(var->tick) >= var->period)
    {
        var->tick = mGetTick();
        var->sum_of_buffer -= var->buffer.p[var->index_buffer];
        var->buffer.p[var->index_buffer] = (float) adc10_read(var->adc_module);
        var->sum_of_buffer += var->buffer.p[var->index_buffer];
        var->average = var->sum_of_buffer / var->buffer.size;
        if (++var->index_buffer >= var->buffer.size)
        {
            var->index_buffer = 0;
        }
        return 1;
    }
    return 0;
}

/*******************************************************************************
 * Function: 
 *      NTC_STATUS fu_adc_ntc(ntc_params_t *var)
 * 
 * Description:
 *      This routine is used to get the temperature of a NTC over an ADC.
 *      It uses the AVERAGE function for the acquisitions.
 * 
 * Parameters:
 *      *var: The pointer of ntc_params_t.
 * 
 * Return:
 *      It returns the status of the NTC acquisition (See. NTC_STATUS enumeration).
 ******************************************************************************/
NTC_STATUS fu_adc_ntc(ntc_params_t *var)
{
    bool ret = fu_adc_average(&var->average);
    
    if (ret)
    {
        return fu_calc_ntc(var->ntc_params, var->pull_up_value, var->average.average, 10, &var->temperature);        
    }
    else
    {
        return NTC_WAIT;
    }
}

/*******************************************************************************
 * Function: 
 *      NTC_STATUS fu_calc_ntc(ntc_settings_t ntc_params, uint32_t ntc_pull_up, uint16_t v_adc, uint8_t adc_resolution, float *p_temperature)
 * 
 * Description:
 *      This routine is used to get the temperature of a NTC from global parameters.
 * 
 * Parameters:
 *      ntc_params:     The parameters of the NTC (R0, T0 & Beta).
 *      ntc_pull_up:    The value of the NTC pull up resistor (in ohms).
 *      v_adc:          The value of the acquisition made by an ADC.
 *      adc_resolution: The ADC resolution (8 for 8-bits, 10 for 10-bits...).
 *                      Because v_adc value is a 16 bits variable, the resolution
 *                      cannot be greater than 16 (for 16-bits).
 *      *p_temperature: A float pointer containing the temperature. 
 * 
 * Return:
 *      It returns the status of the NTC acquisition (See. NTC_STATUS enumeration).
 ******************************************************************************/
NTC_STATUS fu_calc_ntc(ntc_settings_t ntc_params, uint32_t ntc_pull_up, uint16_t v_adc, uint8_t adc_resolution, float *p_temperature)
{
    if (!v_adc)
    {
        return NTC_FAIL_SHORT_CIRCUIT_GND;
    }
    else if (v_adc == (pow(2, adc_resolution) - 1))
    {
        return NTC_FAIL_SHORT_CIRCUIT_VREF;
    }
    else
    {
        *p_temperature = (float) ((1.0/((1.0/(ntc_params.t0+273.15)) + ((1.0/ntc_params.b) * log(((float)(ntc_pull_up / ((pow(2, adc_resolution)/v_adc) - 1.0))) / ntc_params.r0)))) - 273.15); // °C
        return NTC_SUCCESS;
    }
}

/*******************************************************************************
 * Function: 
 *      void fu_hysteresis(hysteresis_params_t *var)
 * 
 * Description:
 *      This routine is used to implement an hysteresis. It can manage as much as
 *      threshold as the user want. 
 * 
 * Parameters:
 *      *var: The pointer of hysteresis_params_t.
 * 
 * Return:
 *      none
 ******************************************************************************/
void fu_hysteresis(hysteresis_params_t *var)
{
    uint8_t i;
    
    for (i = 0 ; i < var->number_of_tipping_threshold ; i++)
    {
        if ((*var->p_input_value >= (var->p_tipping_threshold[i])) && (*var->p_input_value <= (var->p_tipping_threshold[i+1] - var->hysteresis_gap)))               // TIPPING AREA
        {
            if (var->current_threshold != i)
            {
                var->is_updated = true;
                var->current_threshold = i;                
            }
            return;
        }
        else if ((*var->p_input_value < (var->p_tipping_threshold[i + 1])) && (*var->p_input_value > (var->p_tipping_threshold[i + 1] - var->hysteresis_gap)))      // HYSTERESIS AREA
        {
            if ((var->current_threshold < i) || (var->current_threshold > (i + 1)))
            {
                var->is_updated = true;
                var->current_threshold = i;                
            }
            return;
        }
    }
    
    if ((i == var->number_of_tipping_threshold) && (*var->p_input_value >= (var->p_tipping_threshold[i])))
    {
        if (var->current_threshold != i)
        {
            var->is_updated = true;
            var->current_threshold = i;                
        }
        return;
    }
}

/*******************************************************************************
 * Function: 
 *      void fu_bus_management_task(BUS_MANAGEMENT_VAR *dp)
 * 
 * Description:
 *      This routine is used to manage a multitude of devices on a same serial
 *      bus (SPI, UART, I2C). It gives hand to the device which have the greater 
 *      "last execution time" compare to its periodic time.
 *      This function is mandatory when you are using an external peripheral 
 *      (which use itself a serial BUS).
 * 
 * Parameters:
 *      *var: The pointer of BUS_MANAGEMENT_VAR.
 * 
 * Return:
 *      none
 ******************************************************************************/
void fu_bus_management_task(BUS_MANAGEMENT_VAR *var)
{    
    uint8_t i, j;
    uint64_t greater_time = 0, diff_time = 0;
   
    for(i = 0, j = 255 ; i < var->number_of_params ; i++)
    {
        if(var->params[i]->is_running)
        {
            return;
        }
        else 
        {
            diff_time = mTickCompare(var->params[i]->tick);
            if(diff_time >= var->params[i]->waiting_period)
            {
                if ((diff_time - var->params[i]->waiting_period) >= greater_time)
                {
                    j = i;
                    greater_time = diff_time - var->params[i]->waiting_period;
                }
            }
        }
    }
    if (j != 255)
    {
        var->params[j]->is_running = true;
    }
}

/*******************************************************************************
 * Function: 
 *      uint32_t fu_get_integer_value(float v)
 * 
 * Description:
 *      This routine returns the integer value from a float value.
 * 
 * Parameters:
 *      v: The float value.
 * 
 * Return:
 *      The integer result (0..4294967295).
 ******************************************************************************/
uint32_t fu_get_integer_value(float v)
{
    return (uint32_t) v;
}

/*******************************************************************************
 * Function: 
 *      uint32_t fu_get_decimal_value(float v, uint8_t numbers_after_coma)
 * 
 * Description:
 *      This routine returns the decimal value (2 digits after the decimal point)
 *      from a float value.
 *      BECAREFUL !! THE RESULT IS APPROXIMATE WHEN > 3 DECADES AFTER COMA !!
 * 
 * Parameters:
 *      v: The float value.
 * 
 * Return:
 *      The decimal result (0..4294967295).
 ******************************************************************************/
uint32_t fu_get_decimal_value(float v, uint8_t numbers_after_coma)
{
    uint32_t integer = (uint32_t) v;
    uint32_t mult = pow(10, numbers_after_coma);
    return (uint32_t) ((v - (float) integer) * (float) mult);
}

/*******************************************************************************
 * Function: 
 *      float fu_get_float_value(uint32_t integer, uint8_t decimal)
 * 
 * Description:
 *      This routine returns a float value from integer and decimal values.
 * 
 * Parameters:
 *      integer: The integer value (0..4294967295).
 *      decimal: The decimal value (0..99).
 * 
 * Return:
 *      The float result.
 ******************************************************************************/
float fu_get_float_value(uint32_t integer, uint8_t decimal)
{
    return (float) (integer + decimal/100.0);
}
