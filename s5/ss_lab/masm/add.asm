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
        num dw 0000h
        msg db "Enter num: $"
        result_msg db "result is $"

.code
read_num proc
        push ax
        push cx
        push bx

        xor ax, ax        ; clear ax
        xor cx, cx
        mov bx, 10
        mov num, ax
begin_read:
        mov ah, 01h
        int 21h
        xor ah, ah         ; clears ah
        cmp al, 0dh
        je read_end        ;jump out of loop if carriage return is read.

        mov cl, al         ;dl <-- al
        sub cl, 30h        ;convert ASCII into number
        mov ax, num        ;num is loaded into ax
        mul bx             ;DX:AX = AX × BX (32-bit result)
        add ax, cx         ;adds new digit to accumulated result
        mov num, ax        ;result is stored back to location num

        jmp begin_read     ;loop
read_end:
        pop bx
        pop cx
        pop ax
        ret
read_num endp 

print_num proc
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
        call read_num 
        mov ax, num

        print msg
        call read_num

        mov cx, num
        add ax, cx
        print result_msg
        call print_num

        mov ah, 4ch
        int 21h
end start
 
