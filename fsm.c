#include <stdio.h>


void insert_coin(int* pcustomer_coin)
{
    printf("| Insert Coin: ");
    scanf("%d", pcustomer_coin);
}


void move_coin(int *from, int* to)
{
    *to = *from;
    *from -= *from;
}


void move_coin_after(int *from, int* to, int after)
{
    *from -= after;
    move_coin(from, to);
}


void buy_tea(int *pcustomer_coin, int* pmachine_coin)
{
    insert_coin(pcustomer_coin);

    if (*pcustomer_coin < 5)
    {
        *pcustomer_coin = 0;
        printf("| Failed to buy tea. Insufficient coin.\n");
        return;
    }

    move_coin_after(pcustomer_coin, pmachine_coin, 5);
    printf("| Tea purchased. Coin left: %d\n", *pcustomer_coin);
}


void buy_coffee(int *pcustomer_coin, int* pmachine_coin)
{
    insert_coin(pcustomer_coin);

    if (*pcustomer_coin < 10)
    {
        *pcustomer_coin = 0;
        printf("| Failed to buy coffee. Insufficient coin.\n");
        return;
    } 

    move_coin_after(pcustomer_coin, pmachine_coin, 10);
    printf("| Coffee purchased.\n");
}


void refund_excess(int* pcustomer_coin, int* pmachine_coin)
{
    printf("| Refunding excess %d coin\n", *pmachine_coin);
    move_coin(pmachine_coin, pcustomer_coin);
}


void purchase_input(int* ppurchase_id, int* pcoin)
{
    printf("Input for purchase index [1 Coffee | 2 Tea]: ");
    scanf("%d", ppurchase_id);
}


int main()
{    
    int customer_coin = 0,
        machine_coin = 0,
        purchase_id = 0;

    purchase_input(&purchase_id, &customer_coin);
    for(;; purchase_input(&purchase_id, &customer_coin))
    {
        switch (purchase_id)
        {
            case 1: buy_coffee(&customer_coin, &machine_coin); break;
            case 2: buy_tea(&customer_coin, &machine_coin); break;
        }

        if (machine_coin > 0)
            refund_excess(&customer_coin, &machine_coin);
    }

    return 0;
}
