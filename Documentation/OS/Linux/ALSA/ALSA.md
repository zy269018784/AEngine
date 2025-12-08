Types:
    snd_ctl_t
    snd_pcm_info_t
    snd_ctl_elem_list_t
    snd_ctl_elem_info_t
    snd_ctl_elem_value_t
    snd_ctl_elem_id_t
    snd_config_t
    snd_ctl_event_t
    snd_ctl_type_t
    snd_output_t

API:
    CTL interface - primitive controls:
        snd_ctl_open
        snd_ctl_close
        snd_ctl_pcm_info    
        snd_ctl_read
    Give device name hints:
        snd_device_name_hint 
        snd_device_name_free_hint
        snd_device_name_get_hint
    card:    
        snd_card_get_index
        snd_card_next
        snd_card_get_longname
        snd_card_get_name
    element list:
        snd_ctl_elem_list_alloc_space
        snd_ctl_elem_list_free_space
        snd_ctl_elem_list_malloc 
        snd_ctl_elem_list_free
        snd_ctl_elem_list_clear
        snd_ctl_elem_list_get_count
    input:
        snd_input_close
        snd_input_getc
        snd_input_gets
    output:
        snd_output_close        
        snd_output_flush
        snd_output_printf
        snd_output_putc
        snd_output_puts
    pcm:
        snd_pcm_open
        snd_pcm_close
        snd_pcm_pause
        snd_pcm_start
        snd_pcm_drop
        snd_pcm_drain
        snd_pcm_pause
        snd_pcm_writei
        snd_pcm_writen
        snd_pcm_readi
        snd_pcm_readn
        snd_pcm_hw_params
        snd_pcm_prepare
    timer:
        snd_timer_start
        snd_timer_stop
        snd_timer_status
    mixer:
        snd_mixer_open
        snd_mixer_close
        snd_mixer_detach
    config:
        snd_config_add
    global:
        snd_async_add_handler
        snd_async_del_handler
    HwDep Interface (hardware dependent) :
        snd_hwdep_open
        snd_hwdep_close
        snd_hwdep_read
        snd_hwdep_write
    Sequencer Interface:
        snd_seq_open
        snd_seq_close
    Universal MIDI Protocol (UMP) Interface:
        snd_ump_open
        snd_ump_close

Identifying and Opening Control Interfaces
Elements
Identifying Elements
Element Lists

Param:
    List of valid IDs: NAME - name of device DESC - description of device IOID - input / output identification ("Input" or "Output"), NULL means both

    The accepted formats for "string" are:
        The index of the card (as listed in /proc/asound/cards), given as string
        The ID of the card (as listed in /proc/asound/cards)
        The control device name (like /dev/snd/controlC0)











