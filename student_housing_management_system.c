#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LEN 10
#define MAX_TC_LEN 11
#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 15
#define MAX_EMAIL_LEN 50
#define NUM_MONTHS 12
int MONTHLY_RENT = 900;

// Öğrenci bilgilerini tutan yapı
struct Student
{
    char id[MAX_ID_LEN + 1];
    char tc[MAX_TC_LEN + 1];
    char name[MAX_NAME_LEN + 1];
    char surname[MAX_NAME_LEN + 1];
    char gender;
    char dob[11]; // DD.MM.YYYY formatında
    char phone[MAX_PHONE_LEN + 1];
    char email[MAX_EMAIL_LEN + 1];
    char entry_date[11]; // DD.MM.YYYY formatında
    char exit_date[11];  // DD.MM.YYYY formatında
    float deposit;
    int rent_status[NUM_MONTHS];             // 0: ödenmedi, 1: ödendi
    int electricity_bill_status[NUM_MONTHS]; // 0: ödenmedi, 1: ödendi
    float electricity_bill_amount[NUM_MONTHS];
};

// Öğrenci ekleme işlemini yapan fonksiyon
void addStudent()
{
    struct Student student;

    // Öğrenci bilgilerini al
    printf("ID: ");
    scanf("%s", student.id);
    printf("TC: ");
    scanf("%s", student.tc);
    printf("Ad: ");
    scanf("%s", student.name);
    printf("Soyad: ");
    scanf("%s", student.surname);
    printf("Cinsiyet (E/K): ");
    scanf(" %c", &student.gender);
    printf("Doğum tarihi (DD.MM.YYYY): ");
    scanf("%s", student.dob);
    printf("Telefon: ");
    scanf("%s", student.phone);
    printf("E-posta: ");
    scanf("%s", student.email);
    printf("Aparta giriş tarihi (DD.MM.YYYY): ");
    scanf("%s", student.entry_date);
    printf("Aparttan çıkış tarihi (DD.MM.YYYY): ");
    scanf("%s", student.exit_date);
    printf("Depozito bedeli: ");
    scanf("%f", &student.deposit);

    // Kira ve elektrik bilgilerini sıfırla
    for (int i = 0; i < NUM_MONTHS; i++)
    {
        student.rent_status[i] = 0;
        student.electricity_bill_status[i] = 0;
        student.electricity_bill_amount[i] = 0;
    }
    // Öğrenci bilgilerini metin dosyasına yaz
    FILE *fp = fopen("students.txt", "a");
    fprintf(fp, "%s\n%s\n%s\n%s\n%c\n%s\n%s\n%s\n%s\n%s\n%.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dob, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
    for (int i = 0; i < NUM_MONTHS; i++)
    {
        fprintf(fp, "%d %d %.2f\n", student.rent_status[i], student.electricity_bill_status[i], student.electricity_bill_amount[i]);
    }
    fclose(fp);

    printf("\nÖğrenci başarıyla eklendi!\n");
}

// Öğrenci listeleme işlemini yapan fonksiyon
void listStudents()
{
    char tc[MAX_TC_LEN + 1];
    printf("TC: ");
    scanf("%s", tc);
    // Öğrenci bilgilerini metin dosyasından oku
    FILE *fp = fopen("students.txt", "r");
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        // Öğrenci bilgilerini ayır
        struct Student student;
        sscanf(line, "%s", student.id);
        fgets(line, 100, fp);
        sscanf(line, "%s", student.tc);
        if (strcmp(student.tc, tc) == 0)
        {
            // Eşleşen TC bulundu
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dob);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.phone);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.email);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.entry_date);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.exit_date);
            fgets(line, 100, fp);
            sscanf(line, "%f", &student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fgets(line, 100, fp);
                sscanf(line, "%d %d %f", &student.rent_status[i], &student.electricity_bill_status[i], &student.electricity_bill_amount[i]);
            }
            // Öğrenci bilgilerini ekrana yaz
            printf("\nID: %s\n", student.id);
            printf("TC: %s\n", student.tc);
            printf("Ad: %s\n", student.name);
            printf("Soyad: %s\n", student.surname);
            printf("Cinsiyet: %c\n", student.gender);
            printf("Doğum tarihi: %s\n", student.dob);
            printf("Telefon: %s\n", student.phone);
            printf("E-posta: %s\n", student.email);
            printf("Aparta giriş tarihi: %s\n", student.entry_date);
            printf("Aparttan çıkış tarihi: %s\n", student.exit_date);
            printf("Depozito bedeli: %.2f\n", student.deposit);
            printf("Kira durumu:\n");
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                printf("%d. ay: %s\n", i + 1, student.rent_status[i] ? "Ödendi" : "Ödenmedi");
            }
            printf("Elektrik fatura durumu:\n");
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                printf("%d. ay: %s (%.2f TL)\n", i + 1, student.electricity_bill_status[i] ? "Ödendi" : "Ödenmedi", student.electricity_bill_amount[i]);
            }
        }
        else
        {
            // Eşleşmeyen TC, geçici olarak okunan satırları atla
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
            }
        }
    }
    fclose(fp);
}

// Öğrenci silme işlemini yapan fonksiyon
void deleteStudent()
{
    char tc[MAX_TC_LEN + 1];
    printf("TC: ");
    scanf("%s", tc);
    // Öğrenci bilgilerini metin dosyasından oku ve geçici bir dosyaya yaz
    FILE *fp = fopen("students.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        // Öğrenci bilgilerini ayır
        struct Student student;
        sscanf(line, "%s", student.id);
        fgets(line, 100, fp);
        sscanf(line, "%s", student.tc);
        if (strcmp(student.tc, tc) == 0)
        {
            // Eşleşen TC bulundu, öğrenci bilgileri okunmasına gerek yok
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
            }
        }
        else
        {
            // Eşleşmeyen TC, geçici dosyaya yazılacak
            fprintf(temp_fp, "%s", student.id);
            fprintf(temp_fp, "%s", student.tc);
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
                fprintf(temp_fp, "%s", line);
            }
        }
    }
    fclose(fp);
    fclose(temp_fp);

    // Geçici dosyayı orjinal dosya olarak kullan
    remove("students.txt");
    rename("temp.txt", "students.txt");
}
// Öğrenci güncelleme işlemini yapan fonksiyon
void updateStudent()
{
    char tc[MAX_TC_LEN + 1];
    printf("TC: ");
    scanf("%s", tc);
    // Öğrenci bilgilerini metin dosyasından oku ve geçici bir dosyaya yaz
    FILE *fp = fopen("students.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char line[100];

    while (fgets(line, 100, fp) != NULL)
    {
        // Öğrenci bilgilerini ayır
        struct Student student;
        sscanf(line, "%s", student.id);
        fgets(line, 100, fp);
        sscanf(line, "%s", student.tc);
        if (strcmp(student.tc, tc) == 0)
        {
            // Eşleşen TC bulundu, güncellenecek öğrenci
            printf("Yeni ad: ");
            scanf("%s", student.name);
            printf("Yeni soyad: ");
            scanf("%s", student.surname);
            printf("Yeni cinsiyet (E/K): ");
            scanf(" %c", &student.gender);
            printf("Yeni doğum tarihi (DD.MM.YYYY): ");
            scanf("%s", student.dob);
            printf("Yeni telefon: ");
            scanf("%s", student.phone);
            printf("Yeni e-posta: ");
            scanf("%s", student.email);
            printf("Yeni aparta giriş tarihi (DD.MM.YYYY): ");
            scanf("%s", student.entry_date);
            printf("Yeni aparttan çıkış tarihi (DD.MM.YYYY): ");
            scanf("%s", student.exit_date);
            printf("Yeni depozito bedeli: ");
            scanf("%f", &student.deposit);
            // Güncellenen öğrenci bilgileri geçici dosyaya yaz
            fprintf(temp_fp, "%s\n%s\n%s\n%s\n%c\n%s\n%s\n%s\n%s\n%s\n%.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dob, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fgets(line, 100, fp);
                fprintf(temp_fp, "%s", line);
            }
        }
        else
        {
            // Eşleşmeyen TC, geçici dosyaya yazılacak
            fprintf(temp_fp, "%s", student.id);
            fprintf(temp_fp, "%s", student.tc);
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
                fprintf(temp_fp, "%s", line);
            }
        }
    }
    fclose(fp);
    fclose(temp_fp);

    // Geçici dosyayı orjinal dosya olarak kullan
    remove("students.txt");
    rename("temp.txt", "students.txt");

    printf("\nÖğrenci başarıyla güncellendi!\n");
}

// Öğrencinin borç bilgilerini listeleyen fonksiyon
void listDebts()
{
    char id[MAX_ID_LEN + 1];
    printf("ID: ");
    scanf("%s", id);
    // Öğrenci bilgilerini metin dosyasından oku
    FILE *fp = fopen("students.txt", "r");
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        // Öğrenci bilgilerini ayır
        struct Student student;
        sscanf(line, "%s", student.id);
        if (strcmp(student.id, id) == 0)
        {
            // Eşleşen ID bulundu, borç bilgilerini oku
            fgets(line, 100, fp);
            sscanf(line, "%s", student.tc);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dob);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.phone);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.email);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.entry_date);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.exit_date);
            fgets(line, 100, fp);
            sscanf(line, "%f", &student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fgets(line, 100, fp);
                sscanf(line, "%d %d %f", &student.rent_status[i], &student.electricity_bill_status[i], &student.electricity_bill_amount[i]);
            }
            // Borç bilgilerini hesapla
            float total_rent_debt = 0.0;
            float total_electricity_debt = 0.0;
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                if (!student.rent_status[i])
                {
                    total_rent_debt += MONTHLY_RENT;
                }
                if (!student.electricity_bill_status[i])
                {
                    total_electricity_debt += student.electricity_bill_amount[i];
                }
            }
            float total_debt = total_rent_debt + total_electricity_debt + student.deposit;

            // Borç bilgilerini ekrana yaz
            printf("\nID: %s\n", student.id);
            printf("TC: %s\n", student.tc);
            printf("Ad: %s\n", student.name);
            printf("Soyad: %s\n", student.surname);
            printf("Toplam kira borcu: %.2f TL\n", total_rent_debt);
            printf("Toplam elektrik borcu: %.2f TL\n", total_electricity_debt);
            printf("Toplam depozito bedeli: %.2f TL\n", student.deposit);
            printf("Toplam borç: %.2f TL\n", total_debt);
            break;
        }
        else
        {
            // Eşleşmeyen ID, diğer öğrenci bilgilerini atla
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
            }
        }
    }
    fclose(fp);
}

// Öğrencinin kira borcunu ödeyen fonksiyon
void payRent()
{
    char id[MAX_ID_LEN + 1];
    int month;
    printf("ID: ");
    scanf("%s", id);
    printf("Ay: ");
    scanf("%d", &month);

    // Öğrenci bilgilerini metin dosyasından oku ve geçici bir dosyaya yaz
    FILE *fp = fopen("students.txt", "r");

    FILE *temp_fp = fopen("temp.txt", "w");

    char line[100];

    while (fgets(line, 100, fp) != NULL)
    {
        // Öğrenci bilgilerini ayır
        struct Student student;
        sscanf(line, "%s", student.id);
        if (strcmp(student.id, id) == 0)
        {
            // Eşleşen ID bulundu, kira borcunu ödeme işlemi yap
            fgets(line, 100, fp);
            sscanf(line, "%s", student.tc);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dob);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.phone);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.email);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.entry_date);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.exit_date);
            fgets(line, 100, fp);
            sscanf(line, "%f", &student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fgets(line, 100, fp);
                sscanf(line, "%d %d %f", &student.rent_status[i], &student.electricity_bill_status[i], &student.electricity_bill_amount[i]);
                if (i == month - 1)
                {
                    // Ödenen ayın kira durumunu 1 yap (ödendi)
                    student.rent_status[i] = 1;
                }
            }

            // Güncellenen öğrenci bilgileri geçici dosyaya yaz
            fprintf(temp_fp, "%s\n%s\n%s\n%s\n%c\n%s\n%s\n%s\n%s\n%s\n%.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dob, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fprintf(temp_fp, "%d %d %.2f\n", student.rent_status[i], student.electricity_bill_status[i], student.electricity_bill_amount[i]);
            }
        }
        else
        {
            // Eşleşmeyen ID, geçici dosyaya yazılacak
            fprintf(temp_fp, "%s", student.id);
            fprintf(temp_fp, "%s", student.tc);
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
                fprintf(temp_fp, "%s", line);
            }
        }
    }
    fclose(fp);
    fclose(temp_fp);
    // Geçici dosyayı orjinal dosya olarak kullan
    remove("students.txt");
    rename("temp.txt", "students.txt");

    printf("\nKira borcu başarıyla ödendi!\n");
}

// Öğrencinin elektrik borcunu ödeyen fonksiyon
void payElectricityBill()
{
    char id[MAX_ID_LEN + 1];
    int month;
    printf("ID: ");
    scanf("%s", id);
    printf("Ay: ");
    scanf("%d", &month);

    // Öğrenci bilgilerini metin dosyasından oku ve geçici bir dosyaya yaz
    FILE *fp = fopen("students.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        // Öğrenci bilgilerini ayır
        struct Student student;
        sscanf(line, "%s", student.id);
        if (strcmp(student.id, id) == 0)
        {
            // Eşleşen ID bulundu, elektrik borcunu ödeme işlemi yap
            fgets(line, 100, fp);
            sscanf(line, "%s", student.tc);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dob);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.phone);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.email);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.entry_date);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.exit_date);
            fgets(line, 100, fp);
            sscanf(line, "%f", &student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fgets(line, 100, fp);
                sscanf(line, "%d %d %f", &student.rent_status[i], &student.electricity_bill_status[i], &student.electricity_bill_amount[i]);
                if (i == month - 1)
                {
                    // Ödenen ayın elektrik fatura durumunu 1 yap (ödendi)
                    student.electricity_bill_status[i] = 1;
                }
            }
            // Güncellenen öğrenci bilgileri geçici dosyaya yaz
            fprintf(temp_fp, "%s\n%s\n%s\n%s\n%c\n%s\n%s\n%s\n%s\n%s\n%.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dob, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fprintf(temp_fp, "%d %d %.2f\n", student.rent_status[i], student.electricity_bill_status[i], student.electricity_bill_amount[i]);
            }
        }
        else
        {
            // Eşleşmeyen ID, geçici dosyaya yazılacak
            fprintf(temp_fp, "%s", student.id);
            fprintf(temp_fp, "%s", student.tc);
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
                fprintf(temp_fp, "%s", line);
            }
        }
    }
    fclose(fp);
    fclose(temp_fp);
    // Geçici dosyayı orjinal dosya olarak kullan
    remove("students.txt");
    rename("temp.txt", "students.txt");

    printf("\nElektrik borcu başarıyla ödendi!\n");
}

int main()
{
    int choice;
    do
    {
        printf("\n*** APART YONETIM SISTEMI ***\n");
        printf("\n1. Yeni kiraci kaydi icin 1'i seciniz.");
        printf("\n2. Ogrenci kaydini silmek icin 2'i seciniz.");
        printf("\n3. Ogrenci bilgilerini guncellemek icin 3'u seciniz.");
        printf("\n4. Ogrenci bilgilerini isim sirasi A-Z’ye olacak bicimde listelemek icin 4'u seciniz.");
        printf("\n5. Ogrenci borc bilgilerini listelemek icin 5'i seciniz.");
        printf("\n6. Kira borcu odemek icin 6'i seciniz.");
        printf("\n7. Elektrik borcu odemek icin 7'i seciniz.");
        printf("\n8. Cikis yapmak icin 8'i seciniz.");
        printf("\n\nSeciminiz: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            listStudents();
            break;
        case 5:
            listDebts();
            break;
        case 6:
            payRent();
            break;
        case 7:
            payElectricityBill();
            break;
        }
    } while (choice != 8);

    return 0;
}