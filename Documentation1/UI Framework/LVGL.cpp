/*
	1. 链接
	https://docs.lvgl.io/master/
	https://docs.lvgl.io/master/details/widgets/index.html

	2. Overview
		2.1 初始化LVGL
			lv_init													初始化LVGL
		2.2 核心类型
			lv_obj_t												对象
			lv_display_t											显示
			lv_event_t												事件
			lv_style_t												样式
			lv_obj_tree												对象树
			lv_indev_t
			lv_layout_t												布局
			lv_font_t												字体
			lv_theme_t												主题
	3. Displays
		描述
			一个dislpay有多个screen
		类型
			lv_display_t 
		API
			lv_display_create										创建display
			lv_display_delete										删除display
			lv_display_set_resolution								设置display分辨率
			lv_display_get_horizontal_resolution					获取display分辨率宽度
			lv_display_get_vertical_resolution						获取display分辨率高度
			lv_display_set_physical_resolution						设置display物理分辨率
			lv_display_get_physical_horizontal_resolution			获取display物理分辨率宽度
			lv_display_get_physical_vertical_resolution			    获取display物理分辨率高度
			lv_display_set_offset									设置display offset
			lv_display_get_offset_x									获取offset x
			lv_display_get_offset_y									获取offset y
			lv_display_set_dpi										设置display dpi
			lv_display_get_dpi										获取display dpi
			lv_display_set_antialiasing								设置display抗锯齿
			lv_display_get_antialiasing								获取display抗锯齿
			lv_display_register_vsync_event							注册vsync事件
			lv_display_unregister_vsync_event						注销vsync事件
			lv_display_set_user_data								设置display用户数据
			lv_display_get_user_data								获取display用户数据
			lv_display_set_driver_data								设置display驱动数据
			lv_display_get_driver_data								获取display驱动数据
			lv_display_set_theme
			lv_display_get_theme
			lv_display_set_buffers
			lv_display_set_buffers_with_stride
			lv_display_set_draw_buffers
			lv_display_set_3rd_draw_buffer
			lv_display_set_render_mode
			lv_display_set_flush_cb
			lv_display_set_flush_wait_cb
			lv_display_set_color_format
			lv_display_get_color_format
			lv_display_get_original_horizontal_resolution
			lv_display_get_original_vertical_resolution
			lv_display_flush_ready
			lv_display_flush_is_last
			lv_display_get_screen_active
			lv_display_get_screen_prev
			lv_display_get_screen_loading
			lv_display_get_layer_top

	4. Screens

	5. Widgets
		3D Texture (lv_3dtexture)
		Animation Image (lv_animimg)
		Arc (lv_arc)
		Arc Label (lv_arclabel)
		Bar (lv_bar)
		Button (lv_button)
		Button Matrix (lv_buttonmatrix)
		Calendar (lv_calendar)
		Canvas (lv_canvas)
		Chart (lv_chart)
		Checkbox (lv_checkbox)
		Drop-Down List (lv_dropdown)
		Image (lv_image)
		Image Button (lv_imagebutton)
		Keyboard (lv_keyboard)
		Label (lv_label)	
			lv_label_set_text_static
		LED (lv_led)
		Line (lv_line)
		List (lv_list)
		Lottie (lv_lottie)
		Menu (lv_menu)
		Message Box (lv_msgbox)
		Roller (lv_roller)
		Scale (lv_scale)
		Slider (lv_slider)
		Spangroup (lv_spangroup)
		Spinbox (lv_spinbox)
		Spinner (lv_spinner)
		Switch (lv_switch)
		Table (lv_table)
		Tab View (lv_tabview)
		Text Area (lv_textarea)
		Tile View (lv_tileview)
		Window (lv_win)
		New Widget
	
	6. Events
		类型
			lv_event_t 
		API
			lv_obj_send_event					发送事件给对象
			lv_obj_remove_event					对象删除事件
			lv_obj_get_event_count				获取对象的事件数量
			lv_obj_add_event_cb					设置事件回调
			lv_obj_remove_event_cb				删除事件回调
			lv_obj_get_event_dsc				获取事件描述结构体，用于事件管理
			lv_obj_remove_event_dsc				通过事件描述符直接移除事件回调
			lv_event_get_layer					在事件处理中获取相关的图层信息
			lv_event_get_key					从键盘事件中提取按下的键值代码
			lv_event_get_indev					获取触发事件的输入设备（如触摸屏、编码器、键盘等）	
	7. Parts and States

	8. Styles
		类型
			lv_style_t
	9. Theme

	10. Draw

	11. Font

	12. Layout

	13. Subjects and Observers

	14. Objects
		lv_obj_set_style_text_color				设置文本颜色

	15. Examples

	16. lv_obj_t


*/