API:
	lv_obj_add_style				增加样式
	lv_obj_remove_style_all			删除所有样式
	lv_obj_remove_style				删除样式
	lv_obj_replace_style			替换样式
	lv_obj_report_style_change		通知所有对象样式被修改了
	lv_obj_refresh_style			通知一个对象和它的孩子样式被修改了
	lv_obj_style_set_disabled		禁止样式
	lv_obj_style_get_disabled		查询样式是否禁止
	lv_obj_enable_style_refresh		允许样式刷新
	lv_obj_get_style_prop
	lv_obj_has_style_prop
	lv_obj_set_style_pad_all
	lv_obj_set_style_pad_hor
	lv_obj_set_style_pad_ver
	lv_obj_set_style_margin_all
	lv_obj_set_style_margin_hor
	lv_obj_set_style_margin_ver
	lv_obj_set_style_size
	lv_obj_bind_style				绑定样式
	lv_obj_bind_style_prop
	lv_obj_set_style_border_color	设置边框颜色
	lv_obj_set_style_border_opa		设置边框透明度
	lv_obj_set_style_border_width	设置边框宽度
	lv_obj_set_style_border_side
	lv_obj_set_style_border_post
	lv_obj_set_style_outline_color
	lv_obj_set_style_outline_opa
	lv_obj_set_style_outline_width
	lv_obj_set_style_outline_pad
	

状态:
	LV_STATE_DEFAULT: Normal, released state
	LV_STATE_CHECKED: Toggled or checked state
	LV_STATE_FOCUSED: Focused via keypad or encoder or clicked via touchpad/mouse
	LV_STATE_FOCUS_KEY: Focused via keypad or encoder but not via touchpad/mouse
	LV_STATE_EDITED: Edited by an encoder
	LV_STATE_HOVERED: Hovered by mouse
	LV_STATE_PRESSED: Being pressed
	LV_STATE_SCROLLED: Being scrolled
	LV_STATE_DISABLED: Disabled

阴影:
	lv_obj_set_style_shadow_color				阴影颜色
	lv_obj_set_style_shadow_width				阴影宽度
	lv_obj_set_style_shadow_offset_x
	lv_obj_set_style_shadow_offset_y
	lv_obj_set_style_shadow_spread
	lv_obj_set_style_shadow_opa

背景
	lv_obj_set_style_bg_color					背景颜色

边框
	lv_obj_set_style_border_color				边框颜色
	lv_obj_set_style_border_opa					边框透明度
	lv_obj_set_style_border_width				边框宽度
	lv_obj_set_style_border_side
	lv_obj_set_style_border_post

轮廓:
	lv_obj_set_style_outline_color				轮廓颜色	
	lv_obj_set_style_outline_opa				轮廓透明度
	lv_obj_set_style_outline_width				轮廓宽度
	lv_obj_set_style_outline_pad