.model small
.stack 100h

print macro prompt
        push ax
        push dx
        mov ah, 09h
        lea dx, prompt
        int 21h
        pop dx
        pop ax
endm

.data
        msg db "Enter num: $"
        result_msg db " factorial is $"

.code
print_num proc ; prints number in ax
        push ax
        push bx
        push dx

        cmp ax, 0
        je base_case

        mov bx, 10
        xor dx, dx
        div bx
        push dx

        call print_num        ; recursive call

        pop dx
        add dl, 30h
        mov ah, 02h
        int 21h

base_case:
        pop dx
        pop bx
        pop ax
        ret
print_num endp

start:
        mov ax, @data
        mov ds, ax

        print msg
        mov ah, 01h
        int 21h
        sub al, 30h

        xor cx, cx
        mov cl, al

        mov ax, 1
fact_start:
        mul cx
        loop fact_start

        print result_msg
        call print_num

        mov ah, 4ch
        int 21h
end start
