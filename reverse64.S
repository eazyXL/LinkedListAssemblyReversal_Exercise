

.intel_syntax noprefix

.text
.global reverse_asm_64

reverse_asm_64:
push rbx

mov rax, 0x0
mov rbx, rax
mov rcx, rax
mov rdx, rax

mov rax, rdi
cmp rax, 0
je null_ret
add rax, rsi
mov rbx, rax

#ebx = head, ecx = next, edx = newhead
while_start:

cmp rbx, 0x0
je while_done

mov rcx, [rbx]

mov [rbx], rdx

mov rdx, rbx
mov rbx, rcx

jmp while_start

while_done:
mov rax, rdx
sub rax, rsi

null_ret:
pop rbx
ret


