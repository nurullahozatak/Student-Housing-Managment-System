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

// Ogrenci bilgilerini tutan yapi
struct Student
{
    char id[MAX_ID_LEN + 1];
    char tc[MAX_TC_LEN + 1];
    char name[MAX_NAME_LEN + 1];
    char surname[MAX_NAME_LEN + 1];
    char gender;
    char dayofbirth[11]; // DD.MM.YYYY formatinda
    char phone[MAX_PHONE_LEN + 1];
    char email[MAX_EMAIL_LEN + 1];
    char entry_date[11]; // DD.MM.YYYY formatinda
    char exit_date[11];  // DD.MM.YYYY formatinda
    float deposit;
    int rent_status[NUM_MONTHS];             // 0: odenmedi, 1: odendi
    int electricity_bill_status[NUM_MONTHS]; // 0: odenmedi, 1: odendi
    float electricity_bill_amount[NUM_MONTHS];
};

// Ogrenci ekleme islemini yapan fonksiyon
void addStudent()
{
    struct Student student;

    // Ogrenci bilgilerini al
    printf("ID: ");
    scanf("%s", student.id);

    int Saved_id = 0;
    char line[256];
    FILE *fp = fopen("students.txt", "r");
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, student.id))
        {
            Saved_id = 1;
            break;
        }
    }
    fclose(fp);

    if (Saved_id)
    {
        printf("A student with the entered id already exists. Please enter a different id.\n");
        return;
    }

    printf("TC: ");
    scanf("%s", student.tc);

    // Check if the entered tc already exists in the file
    int tcExists = 0;
    fp = fopen("students.txt", "r");
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, student.tc))
        {
            tcExists = 1;
            break;
        }
    }
    fclose(fp);

    if (tcExists)
    {
        printf("A student with the entered tc already exists. Please enter a different tc.\n");
        return;
    }

    printf("Ad: ");
    scanf("%s", student.name);
    printf("Soyad: ");
    scanf("%s", student.surname);
    printf("Cinsiyet (E/K): ");
    scanf(" %c", &student.gender);
    printf("Dogum tarihi (DD.MM.YYYY): ");
    scanf("%s", student.dayofbirth);
    printf("Telefon: ");
    scanf("%s", student.phone);
    printf("E-posta: ");
    scanf("%s", student.email);
    printf("Aparta giris tarihi (DD.MM.YYYY): ");
    scanf("%s", student.entry_date);
    printf("Aparttan cikis tarihi (DD.MM.YYYY): ");
    scanf("%s", student.exit_date);
    printf("Depozito bedeli: ");
    scanf("%f", &student.deposit);

    for (int i = 0; i < NUM_MONTHS; i++)
    {
        student.rent_status[i] = 0;
        student.electricity_bill_status[i] = 0;
        student.electricity_bill_amount[i] = 0;
    }

    for (int i = 0; i < NUM_MONTHS; i++)
    {
        printf("%d. Ay Kira Borcu Durumu: ", i + 1);
        scanf("%d", &student.rent_status[i]);

        printf("%d. Ay Elektrik Borcu Durumu: ", i + 1);
        scanf("%d", &student.electricity_bill_status[i]);

        printf("%d. Ay Elektrik Borcu: ", i + 1);
        scanf("%f", &student.electricity_bill_amount[i]);
    }

    // Ogrenci bilgilerini metin dosyasina yaz
    fp = fopen("students.txt", "a");
    fprintf(fp, "Id: %s\nTC: %s\nIsim: %s\nSoyad: %s\nCisiyet: %c\nDogum Tarihi: %s\nTelefon Numarasi: %s\nE-mail: %s\nGiris Tarihi: %s\nÇikis Tarihi: %s\nDepozito: %.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dayofbirth, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
    for (int i = 0, a = 1; i < 11; i++, a++)
    {
        fprintf(fp, "%d %d %.2f\n", student.rent_status[i], student.electricity_bill_status[i], student.electricity_bill_amount[i]);
    }
    fclose(fp);

    printf("\nOgrenci basariyla eklendi!\n");
}

// Ogrenci silme islemini yapan fonksiyon
void deleteStudent()
{
    
    char id[MAX_ID_LEN + 1];
    printf("Id: ");
    scanf("%s", id);

    // Read the student information from the file and write it to a temporary file
    FILE *fp = fopen("students.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char line[100];
    int idFound = 0;
    while (fgets(line, 100, fp) != NULL)
    {
        // Split the student information
        struct Student student;
        sscanf(line, "Id: %s\nTC: %s\nIsim: %s\nSoyad: %s\nCisiyet: %c\nDogum Tarihi: %s\nTelefon Numarasi: %s\nE-mail: %s\nGiris Tarihi: %s\nÇikis Tarihi: %s\nDepozito: %.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dayofbirth, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
        if (strcmp(student.id, id) == 0)
        {
            // Matching id was found, don't write the student's information to the temporary file
            idFound = 1;
        }
        else
        {
            // No matching id was found, write the student's information to the temporary file
            fprintf(fp, "Id: %s\nTC: %s\nIsim: %s\nSoyad: %s\nCisiyet: %c\nDogum Tarihi: %s\nTelefon Numarasi: %s\nE-mail: %s\nGiris Tarihi: %s\nÇikis Tarihi: %s\nDepozito: %.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dayofbirth, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
                fprintf(temp_fp, "%s", line);
            }
        }
    }
    fclose(fp);
    fclose(temp_fp);

    // Use the temporary file as the original file
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (idFound)
    {
        printf("\nOgrenci basariyla silindi!\n");
    }
    else
    {
        printf("\nBoyle bir ogrenci bulunamadi!\n");
    }
}

// Ogrenci güncelleme islemini yapan fonksiyon
void updateStudent()
{
    char tc[MAX_TC_LEN + 1];
    printf("TC: ");
    scanf("%s", tc);
    // Ogrenci bilgilerini metin dosyasindan oku ve gecici bir dosyaya yaz
    FILE *fp = fopen("students.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char line[100];

    while (fgets(line, 100, fp) != NULL)
    {
        // Ogrenci bilgilerini ayir
        struct Student student;
        sscanf(line, "%s", student.id);
        fgets(line, 100, fp);
        sscanf(line, "%s", student.tc);
        if (strcmp(student.tc, tc) == 1)
        {
            // Eslesen TC bulundu, güncellenecek ogrenci
            printf("Yeni ad: ");
            scanf("%s", student.name);
            printf("Yeni soyad: ");
            scanf("%s", student.surname);
            printf("Yeni cinsiyet (E/K): ");
            scanf(" %c", &student.gender);
            printf("Yeni dogum tarihi (DD.MM.YYYY): ");
            scanf("%s", student.dayofbirth);
            printf("Yeni telefon: ");
            scanf("%s", student.phone);
            printf("Yeni e-posta: ");
            scanf("%s", student.email);
            printf("Yeni aparta giris tarihi (DD.MM.YYYY): ");
            scanf("%s", student.entry_date);
            printf("Yeni aparttan cikis tarihi (DD.MM.YYYY): ");
            scanf("%s", student.exit_date);
            printf("Yeni depozito bedeli: ");
            scanf("%f", &student.deposit);
            // Güncellenen ogrenci bilgileri gecici dosyaya yaz
            fprintf(temp_fp, "Id: %s\nTC: %s\nIsim: %s\nSoyad: %s\nCisiyet: %c\nDogum Tarihi: %s\nTelefon Numarasi: %s\nE-mail: %s\nGiris Tarihi: %s\nÇikis Tarihi: %s\nDepozito: %.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dayofbirth, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fgets(line, 100, fp);
                fprintf(temp_fp, "%s", line);
            }
        }
        else
        {
            // Eslesmeyen TC, gecici dosyaya yazilacak
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

    // Gecici dosyayi orjinal dosya olarak kullan
    remove("students.txt");
    rename("temp.txt", "students.txt");

    printf("\nOgrenci basariyla güncellendi!\n");
}

// Ogrenci listeleme islemini yapan fonksiyon
void listStudents()
{

    char id[MAX_ID_LEN + 1];
    printf("Id: ");
    scanf("%s", id);

    // Ogrenci bilgilerini metin dosyasindan oku
    FILE *fp = fopen("students.txt", "r");
    char line[100];

    while (fgets(line, 100, fp) != NULL)
    {
        // Ogrenci bilgilerini ayir
        struct Student student;
        sscanf(line, "%s", student.tc);
        fgets(line, 100, fp);
        sscanf(line, "%s", student.id);

        if (strcmp(student.id, id) == 0)
        {
            // Eslesen TC bulundu
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dayofbirth);
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
            // Ogrenci bilgilerini ekrana yaz
            printf("\nID: %s\n", student.id);
            printf("TC: %s\n", student.tc);
            printf("Ad: %s\n", student.name);
            printf("Soyad: %s\n", student.surname);
            printf("Cinsiyet: %c\n", student.gender);
            printf("Dogum tarihi: %s\n", student.dayofbirth);
            printf("Telefon: %s\n", student.phone);
            printf("E-posta: %s\n", student.email);
            printf("Aparta giris tarihi: %s\n", student.entry_date);
            printf("Aparttan cikis tarihi: %s\n", student.exit_date);
            printf("Depozito bedeli: %.2f\n", student.deposit);
            printf("Kira durumu:\n");
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                printf("%d. ay: %s\n", i + 1, student.rent_status[i] ? "Odendi" : "Odenmedi");
            }
            printf("Elektrik fatura durumu:\n");
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                printf("%d. ay: %s (%.2f TL)\n", i + 1, student.electricity_bill_status[i] ? "Odendi" : "Odenmedi", student.electricity_bill_amount[i]);
            }
        }
        else
        {
            // Eslesmeyen TC, gecici olarak okunan satirlari atla
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
            }
        }
    }
    fclose(fp);
}

// Ogrencinin borc bilgilerini listeleyen fonksiyon
void listDebts()
{
    char id[MAX_ID_LEN + 1];
    printf("ID: ");
    scanf("%s", id);
    // Ogrenci bilgilerini metin dosyasindan oku
    FILE *fp = fopen("students.txt", "r");
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        // Ogrenci bilgilerini ayir
        struct Student student;
        sscanf(line, "%s", student.id);
        if (strcmp(student.id, id) == 0)
        {
            // Eslesen ID bulundu, borc bilgilerini oku
            fgets(line, 100, fp);
            sscanf(line, "%s", student.tc);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dayofbirth);
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
            // Borc bilgilerini hesapla
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

            // Borc bilgilerini ekrana yaz
            printf("\nID: %s\n", student.id);
            printf("TC: %s\n", student.tc);
            printf("Ad: %s\n", student.name);
            printf("Soyad: %s\n", student.surname);
            printf("Toplam kira borcu: %.2f TL\n", total_rent_debt);
            printf("Toplam elektrik borcu: %.2f TL\n", total_electricity_debt);
            printf("Toplam depozito bedeli: %.2f TL\n", student.deposit);
            printf("Toplam borc: %.2f TL\n", total_debt);
            break;
        }
        else
        {
            // Eslesmeyen ID, diger ogrenci bilgilerini atla
            for (int i = 0; i < NUM_MONTHS + 8; i++)
            {
                fgets(line, 100, fp);
            }
        }
    }
    fclose(fp);
}

// Ogrencinin kira borcunu odeyen fonksiyon
void payRent()
{
    char id[MAX_ID_LEN + 1];
    int month;
    printf("ID: ");
    scanf("%s", id);
    printf("Ay: ");
    scanf("%d", &month);

    // Ogrenci bilgilerini metin dosyasindan oku ve gecici bir dosyaya yaz
    FILE *fp = fopen("students.txt", "r");

    FILE *temp_fp = fopen("temp.txt", "w");

    char line[100];

    while (fgets(line, 100, fp) != NULL)
    {
        // Ogrenci bilgilerini ayir
        struct Student student;
        sscanf(line, "%s", student.id);
        if (strcmp(student.id, id) == 1)
        {
            // Eslesen ID bulundu, kira borcunu odeme islemi yap
            fgets(line, 100, fp);
            sscanf(line, "%s", student.tc);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dayofbirth);
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
                    // Odenen ayin kira durumunu 1 yap (odendi)
                    student.rent_status[i] = 1;
                }
            }

            // Güncellenen ogrenci bilgileri gecici dosyaya yaz
            fprintf(temp_fp, "Id: %s\nTC: %s\nIsim: %s\nSoyad: %s\nCisiyet: %c\nDogum Tarihi: %s\nTelefon Numarasi: %s\nE-mail: %s\nGiris Tarihi: %s\nÇikis Tarihi: %s\nDepozito: %.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dayofbirth, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fprintf(temp_fp, "%d %d %.2f\n", student.rent_status[i], student.electricity_bill_status[i], student.electricity_bill_amount[i]);
            }
        }
        else
        {
            // Eslesmeyen ID, gecici dosyaya yazilacak
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
    // Gecici dosyayi orjinal dosya olarak kullan
    remove("students.txt");
    rename("temp.txt", "students.txt");

    printf("\nKira borcu basariyla odendi!\n");
}

// Ogrencinin elektrik borcunu odeyen fonksiyon
void payElectricityBill()
{
    char id[MAX_ID_LEN + 1];
    int month;
    printf("ID: ");
    scanf("%s", id);
    printf("Ay: ");
    scanf("%d", &month);

    // Ogrenci bilgilerini metin dosyasindan oku ve gecici bir dosyaya yaz
    FILE *fp = fopen("students.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        // Ogrenci bilgilerini ayir
        struct Student student;
        sscanf(line, "%s", student.id);
        if (strcmp(student.id, id) == 1)
        {
            // Eslesen ID bulundu, elektrik borcunu odeme islemi yap
            fgets(line, 100, fp);
            sscanf(line, "%s", student.tc);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.name);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.surname);
            fgets(line, 100, fp);
            sscanf(line, " %c", &student.gender);
            fgets(line, 100, fp);
            sscanf(line, "%s", student.dayofbirth);
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
                    // Odenen ayin elektrik fatura durumunu 1 yap (odendi)
                    student.electricity_bill_status[i] = 1;
                    student.electricity_bill_amount[i] = 0;
                }
            }
            // Güncellenen ogrenci bilgileri gecici dosyaya yaz
            fprintf(temp_fp, "Id: %s\nTC: %s\nIsim: %s\nSoyad: %s\nCisiyet: %c\nDogum Tarihi: %s\nTelefon Numarasi: %s\nE-mail: %s\nGiris Tarihi: %s\nÇikis Tarihi: %s\nDepozito: %.2f\n", student.id, student.tc, student.name, student.surname, student.gender, student.dayofbirth, student.phone, student.email, student.entry_date, student.exit_date, student.deposit);
            for (int i = 0; i < NUM_MONTHS; i++)
            {
                fprintf(temp_fp, "%d %d %.2f\n", student.rent_status[i], student.electricity_bill_status[i], student.electricity_bill_amount[i]);
            }
        }
        else
        {
            // Eslesmeyen ID, gecici dosyaya yazilacak
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
    // Gecici dosyayi orjinal dosya olarak kullan
    remove("students.txt");
    rename("temp.txt", "students.txt");

    printf("\nElektrik borcu basariyla odendi!\n");
}

int main()
{

    int choice;

    while (1)
    {
        printf("\n*** APART YONETIM SISTEMI ***\n");
        printf("\n1. Yeni kiraci kaydi icin 1'i seciniz.");
        printf("\n2. Ogrenci kaydini silmek icin 2'i seciniz.");
        printf("\n3. Ogrenci bilgilerini guncellemek icin 3'u seciniz.");
        printf("\n4. Ogrenci bilgilerini isim sirasi A dan Z ye olacak bicimde listelemek icin 4'u seciniz.");
        printf("\n5. Ogrenci borc bilgilerini listelemek icin 5'i seciniz.");
        printf("\n6. Kira borcu odemek icin 6'i seciniz.");
        printf("\n7. Elektrik borcu odemek icin 7'i seciniz.");
        printf("\n8. Cikis yapmak icin 8'i seciniz.");
        printf("\n\nSeciminiz: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Yeni kiraci kaydi\n");
            addStudent();
        }

        else if (choice == 2)
        {
            printf("Ogrenci kaydi silme\n");
            deleteStudent();
        }

        else if (choice == 3)
        {
            printf("Ogrenci bilgilerini guncelle\n");
            updateStudent();
        }

        else if (choice == 4)
        {
            printf("Ogrenci bilgilerini isim sirasi A dan Z ye olacak bicimde listele\n");
            listStudents();
        }

        else if (choice == 5)
        {
            printf("Ogrenci borc bilgilerini listele\n");
            listDebts();
        }

        else if (choice == 6)
        {
            printf("Kira borcu ode\n");
            payRent();
        }

        else if (choice == 7)
        {
            printf("Elektrik borcu ode\n");
            payElectricityBill();
        }

        else if (choice == 8)
        {
            printf("Program sonlandiriliyor");
            break;
        }
        else
        {
            printf("Lutfen gecerli bir secenek gir !!\n");
            continue;
        }
    }
    return 0;
}
