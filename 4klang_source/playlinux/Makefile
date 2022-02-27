.PHONY: clean # 4klang.o 4klang.asm

.DEFAULT_GOAL := 4klangrender

4klang.asm: ../4klang.asm
	@#sed 's/popad/    \; popad\n    pop rdi\n    pop rsi\n    pop rbp\n    pop rsp\n    pop rbx\n    pop rdx\n    pop rcx\n    pop rax\n\n/g' -i "$@"
	@#sed 's/pushad/    \; pushad\n    pop rax\n    pop rcx\n    pop rdx\n    pop rbx\n    pop rsp\n    pop rbp\n    pop rsi\n    pop rdi\n\n/g' -i "$@"
	@#sed 's/bits/bits 64 \;/' -i "$@"
	@#sed -r 's/push[[:space:]]+e/push r/g' -i "$@"
	@#sed -r 's/pop[[:space:]]+e/pop r/g' -i "$@"
	@#sed -r 's/call[[:space:]]+dword/call qword/g' -i "$@"
	@cp ../4klang.asm .

4klang.inc: ../4klang.inc
	@sed -e 's/\;\%define SINGLE_TICK_RENDERING/\%define SINGLE_TICK_RENDERING/;s/\;\%define AUTHORING/\%define AUTHORING/' ../4klang.inc > 4klang.inc

4klang.o: 4klang.asm 4klang.inc
	@#yasm -m amd64 -f elf64 -o "$@" "$<"
	yasm -m x86 -f elf32 -o "$@" "$<"

4klangrender: 4klang.o 4klangrender.c
	@#gcc -Os -no-pie 4klang.o 4klangrender.c -o "$@"
	gcc -m32 -Os -no-pie 4klang.o 4klangrender.c -o "$@"

run: 4klangrender
	@./4klangrender | sox -t raw -b 32 -e float -r 44100 -c 2 - -d

clean:
	@rm -f 4klang.o 4klang.asm 4klang.inc
