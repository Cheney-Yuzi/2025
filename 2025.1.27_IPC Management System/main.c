#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 结构体
typedef struct 
{
    int id;                 // 序号
    char model[15];         // 型号
    int memory;             // 内存
    int hard_drive;         // 硬盘
    int quantity;           // 数量
    float unit_price;       // 单价
    float total_price;      // 总价
} Purchase_Record;

// 存储采购记录
#define MAX_RECORDS 20
Purchase_Record records[MAX_RECORDS];
int record_count = 0;

// 函数声明
int  Get_User_Choice();                  //用户选择功能 
void Show_Menu();                        //菜单显示
void Write_Records();                    //数据录入
void Display_Records();                  //显示功能
void Save_Records(const char* filename); //存盘功能
void Load_Records(const char* filename); //文件读取功能
void Calculate_Total_Prices();           //计算每种型号的采购总价和本年度总采购额的功能
void Modify_Record();                    //修改采购记录
void Add_Record();                       //增加记录功能
void Delete_Record();                    //删除记录功能
void Sort_Records_Total_Price();         //照总价排序的功能

//用户选择
int Get_User_Choice() 
{
    int choice;
    printf("请输入您的选择：");
    scanf("%d", &choice);

    return choice;
}

//菜单显示
void Show_Menu() 
{
    printf("   请选择功能：\n");
    printf("1. 录入采购记录\n");
    printf("2. 计算单个总价和总采购额\n");
    printf("3. 修改采购记录\n");
    printf("4. 增加采购记录\n");
    printf("5. 删除采购记录\n");
    printf("6. 按总价排序采购记录\n");
    printf("7. 退出\n");
}


//数据录入
void Write_Records() 
{
    int i;
    for (i = 0; i < record_count; i++) 
    {
        printf("请输入第%d条记录的序号：", i + 1);
        scanf("%d", &records[i].id);
        printf("型号(S)：");
        scanf("%s", records[i].model);
        printf("内存(G)：");
        scanf("%d", &records[i].memory);
        printf("硬盘(G)：");
        scanf("%d", &records[i].hard_drive);
        printf("数量(台)：");
        scanf("%d", &records[i].quantity);
        printf("单价(元)：");
        scanf("%f", &records[i].unit_price);
    }
}


//显示功能
void Display_Records() 
{
    int i;
    printf("序号(I)\t型号(S)\t内存(G)\t硬盘(G)\t数量(台)\t单价(元)\t总价(元)\n");
    for (i = 0; i < record_count; i++) 
    {
        printf("%d\t%s\t%d\t%d\t%d\t%.2f\t%.2f\n", records[i].id, records[i].model, records[i].memory,
               records[i].hard_drive, records[i].quantity, records[i].unit_price, records[i].total_price);
    }
}

// 存盘功能
void Save_Records(const char* filename) 
{
    FILE *file = fopen(filename, "wt");
    if (file == NULL) 
    {
        printf("无法打开文件 %s \n", filename);
        return;
    }

    // 写入表头
    fprintf(file, "序号(I)\t型号(S)\t内存(G)\t硬盘(G)\t数量(台)\t单价(元)\t总价(元)\n");

    // 写入记录
    for (int i = 0; i < record_count; i++) 
    {
        fprintf(file, "%d\t%s\t%d\t%d\t%d\t%.2f\t%.2f\n", 
                records[i].id, records[i].model, records[i].memory,
                records[i].hard_drive, records[i].quantity, 
                records[i].unit_price, records[i].total_price);
    }
    
    fclose(file);
    printf("已保存文件 %s。\n", filename);
}

// 文件读取功能
void Load_Records(const char* filename) 
{
    FILE *file = fopen(filename, "rt");
    if (file == NULL) 
    {
        printf("无法打开文件 %s \n", filename);
        return;
    }

    // 跳过表头
    char header[256];
    fgets(header, sizeof(header), file);

    // 读取记录
    fscanf(file, "%d\n", &record_count);
    for (int i = 0; i < record_count; i++) 
    {
        fscanf(file, "%d %s %d %d %d %f %f\n", 
               &records[i].id, records[i].model, &records[i].memory,
               &records[i].hard_drive, &records[i].quantity, 
               &records[i].unit_price, &records[i].total_price);
    }

    fclose(file);
    printf("已读取文件 %s \n", filename);
}

//计算每种型号的采购总价和本年度总采购额的功能
void Calculate_Total_Prices() 
{
    float All_Price = 0;
    for (int i = 0; i < record_count; i++)
    {
        records[i].total_price = records[i].quantity * records[i].unit_price;
        All_Price += records[i].total_price;
    }
    
    printf("本年总采购额为：%.2f元\n", All_Price);

    // 计算完总价后，显示更新后的记录
    Display_Records();

    // 保存更新后的记录
    Save_Records("价格记录_2.txt");
}

//修改采购记录
void Modify_Record() 
{
    int id;
    printf("请输入要修改的记录序号：");
    scanf("%d", &id);

    for (int i = 0; i < record_count; i++) 
    {
        if (records[i].id == id) 
        {
            
            printf("型号(S)：");
            scanf("%s", records[i].model);
            printf("内存(G)：");
            scanf("%d", &records[i].memory);
            printf("硬盘(G)：");
            scanf("%d", &records[i].hard_drive);
            printf("数量(台)：");
            scanf("%d", &records[i].quantity);
            printf("单价(元)：");
            scanf("%f", &records[i].unit_price);
            return;
        }
    }
    printf("未找到序号为%d的记录。\n", id);
}

//增加记录
void Add_Record() 
{
    if (record_count >= MAX_RECORDS) 
    {
        printf("记录已达到最大数量。\n");
        return;
    }

    printf("请输入新记录的序号：");
    scanf("%d", &records[record_count].id);
    printf("型号(S)：");
    scanf("%s", records[record_count].model);
    printf("内存(G)：");
    scanf("%d", &records[record_count].memory);
    printf("硬盘(G)：");
    scanf("%d", &records[record_count].hard_drive);
    printf("数量(台)：");
    scanf("%d", &records[record_count].quantity);
    printf("单价(元)：");
    scanf("%f", &records[record_count].unit_price);

    record_count++;
}

//删除记录
void Delete_Record() 
{
    int id;

    printf("请输入要删除的记录序号：");
    scanf("%d", &id);

    for (int i = 0; i < record_count; i++) 
    {
        if (records[i].id == id) 
        {
            for (int j = i; j < record_count - 1; j++) 
            {
                records[j] = records[j + 1];
            }

            record_count--;

            printf("记录已删除。\n");
            return;
        }
    }
    printf("未找到序号为%d的记录。\n", id);
}

//照总价排序的功能
void Sort_Records_Total_Price() 
{
    Save_Records("价格记录_2.txt");
    for (int i = 0; i < record_count - 1; i++) 
    {
        for (int j = 0; j < record_count - i - 1; j++) 
        {
            if (records[j].total_price > records[j + 1].total_price) 
            {
                Purchase_Record temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

int main() 
{
    int choice;
    record_count = 8; // 初始化记录数量，根据表格中的数据

    while (1) 
    {
        Show_Menu();
        choice = Get_User_Choice();

        switch (choice) 
        {
            case 1:
                Write_Records();
                Display_Records();
                Save_Records("采购记录_1.txt");
                Save_Records("价格记录_2.txt");
                break;

            case 2:
                Calculate_Total_Prices();
                break;

            case 3:
                Modify_Record();
                Save_Records("修改记录_3.txt");
                Calculate_Total_Prices();
                Save_Records("价格记录_2.txt");
                break;

            case 4:
                Add_Record();
                Save_Records("增加记录_4.txt");
                Calculate_Total_Prices();
                Save_Records("价格记录_2.txt");
                break;

            case 5:
                Delete_Record();
                Save_Records("删除记录_5.txt");
                Calculate_Total_Prices();
                Save_Records("价格记录_2.txt");
                break;

            case 6:
                Sort_Records_Total_Price();
                Save_Records("排序记录_6.txt");
                Calculate_Total_Prices();
                Save_Records("价格记录_2.txt");
                break;

            case 7:
                exit(0);

            default:
                printf("无效的选择，请重新输入。\n");
        }
    }

    return 0;
}



