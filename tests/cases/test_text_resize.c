#include <LCUI.h>
#include <ctest-custom.h>

/* clang-format off */

static struct {
	ui_widget_t* block;
	ui_widget_t* inline_block;
} self;

static const char *css = css_string(

.block {
	width: 100px;
	margin: 10px;
	padding: 10px;
	display: block;
	border: 1px solid #f00;
}

.inline-block {
	margin: 10px;
	padding: 10px;
	display: inline-block;
	border: 1px solid #f00;
}

.short-content {
	content: "hello!";
}

.long-content {
	content: "this is long long long long long long long text";
}

);

/* clang-format on */

static void build(void)
{
        ui_widget_t *root;

        ui_load_css_string(css, __FILE__);

        self.block = ui_create_widget("text");
        self.inline_block = ui_create_widget("text");

        ui_widget_set_id(self.block, "debug-block");
        ui_widget_set_id(self.inline_block, "debug-inline-block");
        ui_text_set_content_w(self.block, L"block");
        ui_text_set_content_w(self.inline_block, L"inline block");
        ui_widget_add_class(self.block, "block");
        ui_widget_add_class(self.inline_block, "inline-block");

        root = ui_root();
        ui_widget_append(root, self.block);
        ui_widget_append(root, self.inline_block);
}

static void test_text_set_content(void *arg)
{
        ui_text_set_content(self.inline_block,
                            "long long long long long long long "
                            "long long long long long long long "
                            "long long long long long long long text");

        ui_text_set_content(self.block,
                            "long long long long long long long "
                            "long long long long long long long "
                            "long long long long long long long text");
}

static void check_text_set_content(void)
{
        ui_update();

        ctest_equal_bool("check block width",
                         self.block->border_box.width == 122.0f, TRUE);
        ctest_equal_bool("check block height",
                         self.block->border_box.height > 140.0f, TRUE);
        ctest_equal_bool("check inline block width",
                         self.inline_block->border_box.width > 520.0f, TRUE);
        ctest_equal_bool("check inline block height",
                         self.inline_block->border_box.height < 45.0f, TRUE);
}

static void test_text_set_short_content_css(void *arg)
{
        ui_widget_add_class(self.block, "short-content");
        ui_widget_add_class(self.inline_block, "short-content");
}

static void check_text_set_short_content_css(void)
{
        ui_update();

        ctest_equal_bool("check block width",
                         self.block->border_box.width == 122.0f, TRUE);
        ctest_equal_bool("check block height",
                         self.block->border_box.height < 45.0f, TRUE);
        ctest_equal_bool("check inline block width",
                         self.inline_block->border_box.width < 70.0f, TRUE);
        ctest_equal_bool("check inline block height",
                         self.inline_block->border_box.height < 45.0f, TRUE);
}

static void test_text_set_long_content_css(void *arg)
{
        ui_widget_remove_class(self.block, "short-content");
        ui_widget_remove_class(self.inline_block, "short-content");
        ui_widget_add_class(self.block, "long-content");
        ui_widget_add_class(self.inline_block, "long-content");
}

static void check_text_set_long_content_css(void)
{
        ui_update();

        ctest_equal_bool("check block width",
                         self.block->border_box.width == 122.0f, TRUE);
        ctest_equal_bool("check block height",
                         self.block->border_box.height > 60.0f, TRUE);
        ctest_equal_bool("check inline block width",
                         self.inline_block->border_box.width > 250.0f, TRUE);
        ctest_equal_bool("check inline block height",
                         self.inline_block->border_box.height < 45.0f, TRUE);
}

void test_text_resize(void)
{
        lcui_init();

        build();

        test_text_set_content(NULL);
        ctest_describe("check text set content", check_text_set_content);
        test_text_set_short_content_css(NULL);
        ctest_describe("check text set short content css",
                       check_text_set_short_content_css);
        test_text_set_long_content_css(NULL);
        ctest_describe("check text set long content css",
                       check_text_set_long_content_css);

        lcui_quit();
        lcui_main();
}
