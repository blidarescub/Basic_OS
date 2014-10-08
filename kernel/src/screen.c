// Basic Operating System.
// Printing on the screen.

#include <screen.h>
#include <memory.h>
#include <types.h>

u16 *video_buffer;
int cursor_column;
int cursor_row;

// Initialize the screen.
void init_screen (void)
{
    video_buffer = (u16 *) 0xB8000;
    cursor_column = 0;
    cursor_row = 0;
}

// Clear the screen.
void clear_screen (void)
{
    memset ((u8 *) 0xB8000, 0, VBUFFER_SIZE);
    cursor_column = 0;
    cursor_row = 0;
}

// Scroll the screen.
void scroll_screen (void)
{
    memcpy ((u8 *) 0xB8000, (u8 *) 0xB8000 + SCREEN_WIDTH * 2,
			VBUFFER_SIZE - SCREEN_WIDTH * 2);
    memset ((u8 *) 0xB8000 + VBUFFER_SIZE - SCREEN_WIDTH * 2, 0,
			SCREEN_WIDTH * 2);
    cursor_row = SCREEN_HEIGHT - 1;
    cursor_column = 0;
}

// Draw a character on the screen at the specified position.
void putch_at (char ch, int column, int row)
{
    int offset = (row * SCREEN_WIDTH) + column;
    video_buffer[offset] = ch | (0x07 << 8);
}

// Go to the next line.
static inline void newline (void)
{
    ++cursor_row;
    cursor_column = 0;
    if (cursor_row >= SCREEN_HEIGHT)
        scroll_screen ();
}

// Implement backspace.
static inline void backspace (void)
{
    if (cursor_column > 0)
    {
        --cursor_column;
        putch (' ');
        --cursor_column;
    }
}

// Draw a character at the cursor position.
void putch (char ch)
{
    if (ch == '\n')
    {
        newline ();
    }
    else if (ch == '\b')
    {
        backspace ();
    }
    else
    {
        putch_at (ch, cursor_column, cursor_row);

        ++cursor_column;
        if (cursor_column >= SCREEN_WIDTH)
        {
            ++cursor_row;
            cursor_column = 0;
            if (cursor_row >= SCREEN_HEIGHT)
            {
                scroll_screen ();
            }
        }
    }
}

// Draw a string starting at the cursor position.
void puts (const char *s)
{
    int i;
    for (i = 0; s[i] != 0; ++i)
    {
        putch (s[i]);
    }
}
