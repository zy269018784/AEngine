/*
	1. 

	2. 
	Window

	3. DispatcherObject类
	DispatcherObject
		DependencyObject
			Visual
				UIElement
					FrameworkElement
						Control
							ContentControl
								ButtonBase
									Button
						Panel
							StackPanel
						Shape
							Rectangle
	4. 控件
	DependencyObject
		|-Visual
		|	|-UIElement
		|	|	|-FrameworkElement
		|	|	|	|-Panel 
		|	|	|	|	|-Grid(网格布局)
		|	|	|	|	|-UniformGrid(均分布局)
		|	|	|	|	|-StackPanel(栈式布局)
		|	|	|	|	|-WrapPanel(瀑布流布局)
		|	|	|	|	|-DockPanel(停靠布局)
		|	|	|	|	|-Canvas(绝对布局)
		|	|	|	|	|-Border(边框布局)
		|	|	|	|-Control
		|	|	|	|	|-ContentControl 
		|	|	|	|	|	|-ButtonBase 
		|	|	|	|	|	|	|-Button(普通按钮)
		|	|	|	|	|	|	|-ToggleButton
		|	|	|	|	|	|	|	|-CheckBox(复选框按钮)
		|	|	|	|	|	|	|	|-RadioButton(单选框按钮)
		|	|	|	|	|	|	|-RepeatButton(重复按钮)
		|	|	|	|	|	|	|-GridViewColumnHeader
		|	|	|	|	|	|	|-DataGridColumnHeader
		|	|	|	|	|	|	|-DataGridRowHeader
		|	|	|	|	|	|-Label(标签)
		|	|	|	|	|-TextBoxBase
		|	|	|	|	|	|-TextBox(文本框)
		|	|	|	|	|	|-RichTextBox(富文本框)
		|	|	|	|	|-ToolTip(提示工具)
		|	|	|	|	|-HeaderedContentControl 
		|	|	|	|	|	|-Expander(折叠控件) 
		|	|	|	|	|-ScrollViewer
		|	|	|	|	|-RangeBase 
		|	|	|	|	|	|-ScrollBar(滚动条)
		|	|	|	|	|	|-Slider(滑动条)
		|	|	|	|	|	|-ProgressBar(进度条) 
		|	|	|	|	|-Calendar(日历控件) 
		|	|	|	|	|-DatePicker(日期控件)
		|	|	|	|	|-ItemsControl
		|	|	|	|	|	|-Selector 
		|	|	|	|	|	|	|-ListBox(列表控件)
		|	|	|	|	|	|	|	|-ListView(数据列表控件) 
		|	|	|	|	|	|	|-MultiSelector 
		|	|	|	|	|	|	|	|-DataGrid 
		|	|	|	|	|	|	|-ComboBox(下拉框控件)
		|	|	|	|	|	|	|-TabControl 
		|	|	|	|	|	|-TreeView(树控件) 
		|	|	|	|-TextBlock
		|	|	|	|-Popup(弹出窗口)
		|	|	|	|-Image(图像控件)
		|	|	|	|-Shape
		|	|	|	|	|-Ellipse(椭圆)
		|	|	|	|	|-Line(线段)
		|	|	|	|	|-Rectangle(矩形)
		|	|	|	|	|-Polyline(曲线)
		|	|	|	|	|-Polygon(多边形)
		|	|	|	|	|-Path(路径)
		|-Style
*/			 