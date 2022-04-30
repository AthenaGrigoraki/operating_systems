#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/d_params.h>
#include <asm-generic/errno-base.h> /*error values are defined here*/
#include <asm/current.h> /*inline function of current process*/
#include <linux/sched.h> /*struct task_struct*/
#include <linux/types.h> /*pid_t*/

asmlinkage long set_deadlines(int pid, unsigned long deadline, unsigned long computation_time){


    printk("Athina Grigoraki, csd4109, set_deadlines syscall has been called\n"); /*message that prints at kernel*/
    printk("Called set_deadlines with arguments %d, %lu, %lu\n", pid, deadline, computation_time);
    if(!(deadline > computation_time)){
        printk("computation time > deadline , kernel cant fulfill requirement of process\n");
        return EINVAL;
    }

    if(pid < -1){
        return EINVAL;
    }else if(pid == -1){ /*mas endiaferei i trexousa diergasia*/
        current->deadline = deadline;
        current->computation_time= computation_time;

        return 0;
    }else{
    struct task_struct *structs;
        for_each_process(structs){ /*access all processes*/
            if(structs->pid == pid){
                structs->deadline=deadline;
                structs->computation_time=computation_time;
                printk("task_struct: remaining computation time is %lu and deadline is %lu\n",current->computation_time, current->deadline);
                return 0;
            }
        }
    }

    return EINVAL; /*when syscall in not a success , error value returns*/

}
