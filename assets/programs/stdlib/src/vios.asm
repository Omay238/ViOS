[BITS 32]

section .asm

global vios_exit:function
global print:function
global vios_getkey:function
global vios_malloc:function
global vios_free:function
global vios_putchar:function
global vios_process_load_start:function
global vios_system:function
global vios_process_get_arguments:function
global vios_sleep:function
global vios_read:function

; void vios_exit()
vios_exit:
    push ebp
    mov ebp, esp
    mov eax, 0 ; Command 0 process exit
    int 0x80
    pop ebp
    ret

; void print(const char* filename)
print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax, 1 ; Command print
    int 0x80
    add esp, 4
    pop ebp
    ret

; int vios_getkey()
vios_getkey:
    push ebp
    mov ebp, esp
    mov eax, 2 ; Command getkey
    int 0x80
    pop ebp
    ret

; void vios_putchar(char c)
vios_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3 ; Command putchar
    push dword [ebp+8] ; Variable "c"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void* vios_malloc(size_t size)
vios_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4 ; Command malloc (Allocates memory for the process)
    push dword[ebp+8] ; Variable "size"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void vios_free(void* ptr)
vios_free:
    push ebp
    mov ebp, esp
    mov eax, 5 ; Command 5 free (Frees the allocated memory for this process)
    push dword[ebp+8] ; Variable "ptr"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void vios_process_load_start(const char* filename)
vios_process_load_start:
    push ebp
    mov ebp, esp
    mov eax, 6 ; Command 6 process load start ( stars a process )
    push dword[ebp+8] ; Variable "filename"
    int 0x80
    add esp, 4
    pop ebp
    ret

; int vios_system(struct command_argument* arguments)
vios_system:
    push ebp
    mov ebp, esp
    mov eax, 7 ; Command 7 process_system ( runs a system command based on the arguments)
    push dword[ebp+8] ; Variable "arguments"
    int 0x80
    add esp, 4
    pop ebp
    ret


; void vios_process_get_arguments(struct process_arguments* arguments)
vios_process_get_arguments:
    push ebp
    mov ebp, esp
    mov eax, 8 ; Command 8 Gets the process arguments
    push dword[ebp+8] ; Variable arguments
    int 0x80
    add esp, 4
    pop ebp
    ret

; void vios_sleep(int seconds)
vios_sleep:
    push ebp
    mov ebp, esp
    mov eax, 9
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

; char* vios_read(const char* filename)
vios_read:
    push ebp
    mov ebp, esp
    mov eax, 10
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret