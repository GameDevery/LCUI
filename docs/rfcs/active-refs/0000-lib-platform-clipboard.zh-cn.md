- 开始日期：2023-04-09
- 目标主要版本：3.x
- 参考问题：[#216](https://github.com/lc-soft/LCUI/issues/216)
- 实现 PR：[#271](https://github.com/lc-soft/LCUI/pull/271)

# 概括

添加剪切板支持，使 TextEdit 文本编辑框部件能够响应文本的复制粘贴操作。

# 基本示例

响应粘贴（Paste）事件：

```c
void on_paste(ui_widget_t *w, ui_event_t *e, void *arg)
{
	clipboard_t *clipboard = arg;

	if (clipboard && clipboard->text) {
        printf("paste text: %ls\n", clipboard->text);
	}
}

void example(void)
{
    ui_widget_t *text = ui_create_widget("textedit");
    ui_widget_on(text2, "paste", on_paste, NULL, NULL);
}
```

设置剪切板内容：

```c
wchar_t text[32] = L"hello, world!";

clipboard_set_text(text, 32);
```

获取剪切板内容：

```c
void on_clipboard_ready(clipboard_t *clipboard, void *arg)
{
	if (clipboard && clipboard->text) {
        printf("clipboard text: %ls\n", clipboard->text);
	}
}

void exmaple(void)
{
    clipboard_request_text(on_clipboard_ready, NULL);
}
```

# 动机

TextEdit 文本编辑部件仅能够响应按键输入，无法复制其它地方的文本内容粘贴到该部件内。

# 详细设计

在 X11 窗口系统中，剪切板中的数据是无法以同步的方式获取的，我们需要通过使用一些变量来调用 `XConverSelection()`，在收到 SelectionNotify 事件后复制剪贴板时，我们需要存储和引用这些变量。

为适应这种异步的调用方式，剪切板的用法应该设计成先请求文本，然后在回调函数中处理请求到的文本。

具体接口设计如下：

```c
LIBPLAT_PUBLIC int clipboard_request_text(clipboard_callback_t action, void *arg);
LIBPLAT_PUBLIC int clipboard_set_text(const wchar_t *text, size_t len);
LIBPLAT_PUBLIC void clipboard_init(void);
LIBPLAT_PUBLIC void clipboard_destroy(void);
```

# 缺点

无。

# 备选方案

无。

# 采用策略

这是新增功能，需要修改 TextEdit 部件，增加 Ctrl+C、Ctrl+V 快捷键响应支持，以及剪切板接口调用。

平台库 libplatform 内增加适用于 x11 窗口系统的剪切板支持模块，对于不支持的系统，默认将全局变量作为剪切板数据源。

# 未解决的问题

未实现 Windows 系统的剪切板支持。

`x11_clipboard_set_text()` 的 len 参数没有用到，考虑移除。
