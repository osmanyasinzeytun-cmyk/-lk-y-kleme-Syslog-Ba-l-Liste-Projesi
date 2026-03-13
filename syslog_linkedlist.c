#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 
typedef struct SyslogNode {
    int logID;                      // Her kayýt için benzersiz kimlik
    char logContent[512];           // Log mesajýnýn içeriði
    struct SyslogNode *nextAddress; // Bir sonraki düðümün adresi
    struct SyslogNode *prevAddress; // Bir önceki düðümün adresi
} SyslogNode;

// Liste kontrol iþaretçileri
SyslogNode *headNode = NULL;
SyslogNode *tailNode = NULL;

/**
 * @brief Yeni bir günlüðü listenin sonuna ekler.
 * @param line Okunan log satýrý
 */
void add_log_to_list(char *line) {
    SyslogNode *newNode = (SyslogNode*)malloc(sizeof(SyslogNode));
    if (newNode == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return;
    }

    static int idCounter = 1;
    newNode->logID = idCounter++;
    strcpy(newNode->logContent, line);
    
    newNode->nextAddress = NULL;

    if (headNode == NULL) {
        newNode->prevAddress = NULL;
        headNode = tailNode = newNode;
    } else {
        tailNode->nextAddress = newNode;
        newNode->prevAddress = tailNode;
        tailNode = newNode;
    }
}

/**
 * @brief Syslog dosyasýný okur ve listeye aktarýr.
 */
void process_syslog_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("HATA: %s dosyasi acilamadi!\n", path);
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        add_log_to_list(buffer);
    }
    fclose(file);
}

/**
 * @brief Listeyi baþtan sona (Eskiden Yeniye) yazdýrýr.
 */
void print_logs_forward() {
    SyslogNode *current = headNode;
    printf("\n--- [ILERI] SYSLOG KAYITLARI (KRONOLOJIK) ---\n");
    while (current != NULL) {
        printf("ID: %d | %s", current->logID, current->logContent);
        current = current->nextAddress;
    }
}

/**
 * @brief Listeyi sondan baþa (Yeniden Eskiye) yazdýrýr.
 * Çift yönlü baðlý listenin en büyük avantajýdýr.
 */
void print_logs_backward() {
    SyslogNode *current = tailNode;
    printf("\n--- [GERI] SYSLOG KAYITLARI (EN YENI ILK) ---\n");
    while (current != NULL) {
        printf("ID: %d | %s", current->logID, current->logContent);
        current = current->prevAddress;
    }
}

/**
 * @brief Program kapanýrken belleði temizler.
 */
void cleanup_memory() {
    SyslogNode *current = headNode;
    while (current != NULL) {
        SyslogNode *temp = current;
        current = current->nextAddress;
        free(temp);
    }
}

int main() {
    const char *fileName = "syslog.txt";

    // 1. Veri Giriþi
    process_syslog_file(fileName);

    // 2. Eðer dosya boþsa veya açýlmadýysa boþ görünmesin diye manuel veri (Demo için)
    if (headNode == NULL) {
        printf("\n[UYARI] Dosya bulunamadi veya bos. Manuel veri ekleniyor...\n");
        add_log_to_list("Mar 13 23:10:01 kernel: CPU temperature 45C\n");
        add_log_to_list("Mar 13 23:12:45 auth: User 'osman' logged in\n");
    }

    // 3. Çýktýlar
    print_logs_forward();
    print_logs_backward();

    // 4. Güvenli Çýkýþ
    cleanup_memory();
    
    printf("\nSunum tamamlandi. Cikmak icin bir tusa basin.");
    getchar(); 
    return 0;
}
