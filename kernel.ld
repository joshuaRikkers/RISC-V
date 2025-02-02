/* カーネルのエントリポイント*/
ENTRY(boot)

SECTIONS {
    /* ベースアドレス*/
    . = 0x80200000;

    /* コードのりょういき*/
    .text :{
        KEEP(*(.text.boot));
        *(.text .text.*);
    }

    /* 定数(literal) データりょういき。
     * 読み取りしかできません。*/
    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }

    /* 読み書き可能データりょういき*/
    .data : ALIGN(4) {
        *(.data .data.*);
    }

    /* 読み書き可能
     * .dataと違い、初期値がゼロの変数を
     * 配置する。*/
    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    . = ALIGN(4);
    . += 128 * 1024; /* 128KB */
    __stack_top = .;
}
