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

API: 
    snd_pcm_open
    snd_pcm_close
    snd_pcm_pause
    snd_device_name_hint 
    snd_device_name_free_hint
    snd_device_name_get_hint
    snd_ctl_open
    snd_ctl_close
    snd_ctl_pcm_info    
    snd_ctl_read
    
    snd_card_get_index
    snd_card_next
    snd_card_get_longname
    snd_card_get_name
    
    snd_ctl_elem_list_alloc_space
    snd_ctl_elem_list_free_space

    snd_ctl_elem_list_malloc 
    snd_ctl_elem_list_free
    snd_ctl_elem_list_clear
    snd_ctl_elem_list_get_count

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











