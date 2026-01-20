#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> // Türkçe karakterler için

#define MAX_QUESTIONS_lVL 5
#define NUM_LVL 12
#define MAX_NAME_LENGTH 50

struct Question {
    int level_no;
    char question[256];
    char choiceA[128];
    char choiceB[128];
    char choiceC[128];
    char choiceD[128];
    char correctChoice;
};

// Fonksiyon Tanımları (Senin yapınla aynı)
struct Question readQuestions(const char* filename, int levelNo);
void startGame(int *levelNo);
void askQuestion(const struct Question* question, int* playerWinnings, int* currentLevel, int* correctAnswers);
void checkAnswer(const struct Question* question, char choice, int* playerWinnings, int* currentLevel, int* correctAnswers);
void useFiftyFifty(const struct Question* question);
void useDoubleDip(const struct Question* question, int* playerWinnings, int* currentLevel, int* correctAnswers);
void savePlayerWinnings(int playerWinnings);
int calculateWinnings(int correctAnswers);
void showReport();

// MAIN FONKSIYONU
int main(void) {
    setlocale(LC_ALL, "Turkish"); // Türkçe karakterleri düzeltir
    srand(time(NULL));

    printf("Kim milyoner olmak ister yarışmasına hoş geldiniz.! -- 777 --\n");
    printf("1. Yeni oyunu başlayalım\n");
    printf("2. Sonuçları görüntüle\n");
    printf("Bir seçim(choice) yapınız: ");

    int choice;
    int levelNo = 1;

    scanf("%d", &choice);
    switch(choice) {
        case 1:
            startGame(&levelNo);
            break;
        case 2:
            showReport();
            break;
        default:
            printf("Geçersiz bir seçim yaptınız. 1 ya da 2. seçimden birini yapınız.!!\n");
    }

    return 0;
}

// SENİN LOGİĞİNLE DÜZELTİLMİŞ DOSYA OKUMA
struct Question readQuestions(const char* filename, int levelNo) {
    // BURAYA SENİN TAM YOLUNU YAZDIM:
    FILE* file = fopen("C:\\Users\\minea\\Desktop\\MilyonerOyunu\\question.csv", "r");

    struct Question q = {0};
    struct Question candidateQuestions[50]; // O seviyenin sorularını tutacak havuz
    int count = 0;

    if (file == NULL) {
        printf("HATA: Dosya acilamadi!\n");
        printf("Yol: C:\\Users\\minea\\Desktop\\MilyonerOyunu\\question.csv\n");
        exit(1);
    }

    char line[512];

    // Senin "satır satır okuma" mantığını güvenli hale getirdim
    while(fgets(line, sizeof(line), file)) {
        char tempLine[512];
        strcpy(tempLine, line);

        // İlk token (Boş mu diye kontrol ediyoruz)
        char* token = strtok(tempLine, ",");
        if(token == NULL) continue;

        // İkinci token: Level No
        token = strtok(NULL, ",");
        if(token == NULL) continue;
        int currentLevel = atoi(token);

        // Eğer dosyadaki soru, aradığımız level ise alalım
        if (currentLevel == levelNo) {
            q.level_no = currentLevel;

            token = strtok(NULL, ","); strcpy(q.question, token ? token : "");
            token = strtok(NULL, ","); strcpy(q.choiceA, token ? token : "");
            token = strtok(NULL, ","); strcpy(q.choiceB, token ? token : "");
            token = strtok(NULL, ","); strcpy(q.choiceC, token ? token : "");
            token = strtok(NULL, ","); strcpy(q.choiceD, token ? token : "");

            token = strtok(NULL, ",");
            if(token) q.correctChoice = token[0];

            // Havuza ekle
            candidateQuestions[count] = q;
            count++;
            if(count >= 50) break;
        }
    }

    fclose(file); // Dosyayı kapatıyoruz (Senin kodunda return sonrasındaydı, o yüzden kapanmıyordu)

    if(count == 0) {
        printf("Hata: %d. seviye icin soru bulunamadi.\n", levelNo);
        exit(1);
    }

    // Bulunan sorulardan rastgele birini seçip döndürüyoruz
    int randomIndex = rand() % count;
    return candidateQuestions[randomIndex];
}

// OYUNU BAŞLATAN FONKSİYON
void startGame(int *levelNo) {
    int playerWinnings = 0;
    int currentLevel = 0;
    int correctAnswers = 0;

    // Senin döngü yapın
    for (int i = 0; i < NUM_LVL; i++) {
        *levelNo = i + 1;
        // readQuestions'ı düzelttik, artık struct döndürüyor
        struct Question currentQ = readQuestions("question.csv", *levelNo);

        askQuestion(&currentQ, &playerWinnings, &currentLevel, &correctAnswers);
        currentLevel++;
    }

    printf("\n1 Milyonluk soruyu da cevapladınız. Tebrikler milyonersiniz.!\n");
    printf("Total kazancınız: %d TL\n", playerWinnings);
    savePlayerWinnings(playerWinnings);
}

// SORU SORMA FONKSİYONU (Senin recursion mantığın korundu)
void askQuestion(const struct Question* question, int* playerWinnings, int* currentLevel, int* correctAnswers) {
    printf("\nLevel %d\n", (*currentLevel) + 1);
    printf("%s\n", question->question);
    printf("A. %s\n", question->choiceA);
    printf("B. %s\n", question->choiceB);
    printf("C. %s\n", question->choiceC);
    printf("D. %s\n", question->choiceD);
    printf("Enter your answer (A/B/C/D) or 'L' for Lifeline: ");

    char choice;
    scanf(" %c", &choice);

    // Küçük harf girilirse büyütelim
    if(choice >= 'a' && choice <= 'z') choice -= 32;

    switch(choice) {
        case 'L':
            {
                printf("Bir joker seçimi yapın:\n");
                printf("1. 50/50\n");
                printf("2. Double Dip\n");
                printf("seçimizi yapın: ");
                int lifelineChoice;
                scanf("%d", &lifelineChoice);
                switch(lifelineChoice) {
                    case 1:
                        useFiftyFifty(question);
                        // Jokerden sonra tekrar soruyu sormak yerine cevabı istiyoruz (Recursion riskli olabilir diye düzelttim)
                        printf("Lütfen kalan şıklardan cevabınızı verin: ");
                        scanf(" %c", &choice);
                        if(choice >= 'a' && choice <= 'z') choice -= 32;
                        checkAnswer(question, choice, playerWinnings, currentLevel, correctAnswers);
                        break;
                    case 2:
                        useDoubleDip(question, playerWinnings, currentLevel, correctAnswers);
                        break;
                    default:
                        printf("Geçersiz seçim.\n");
                        // Recursion: Tekrar soruyu sor
                        askQuestion(question, playerWinnings, currentLevel, correctAnswers);
                }
                return;
            }
        default:
            checkAnswer(question, choice, playerWinnings, currentLevel, correctAnswers);
    }
}

// KAZANÇ HESAPLAMA
int calculateWinnings(int correctAnswers) {
    switch (correctAnswers) {
        case 0: return 0;
        case 1: return 500;
        case 2: return 1000;
        case 3: return 2000;
        case 4: return 3000;
        case 5: return 5000;
        case 6: return 7500;
        case 7: return 15000;
        case 8: return 30000;
        case 9: return 60000;
        case 10: return 125000;
        case 11: return 250000;
        case 12: return 1000000;
        default: return 0;
    }
}

// 50/50 JOKERİ
void useFiftyFifty(const struct Question* question) {
    char correctChoice = question->correctChoice;
    char wrongChoice;
    do {
        wrongChoice = 'A' + rand() % 4;
    } while (wrongChoice == correctChoice);

    printf("Remaining choices:\n");
    // Şıkları sırasıyla yazdıralım
    if (correctChoice < wrongChoice) {
        if(correctChoice == 'A' || wrongChoice == 'A') printf("A. %s\n", question->choiceA);
        if(correctChoice == 'B' || wrongChoice == 'B') printf("B. %s\n", question->choiceB);
        if(correctChoice == 'C' || wrongChoice == 'C') printf("C. %s\n", question->choiceC);
        if(correctChoice == 'D' || wrongChoice == 'D') printf("D. %s\n", question->choiceD);
    } else {
        if(wrongChoice == 'A' || correctChoice == 'A') printf("A. %s\n", question->choiceA);
        if(wrongChoice == 'B' || correctChoice == 'B') printf("B. %s\n", question->choiceB);
        if(wrongChoice == 'C' || correctChoice == 'C') printf("C. %s\n", question->choiceC);
        if(wrongChoice == 'D' || correctChoice == 'D') printf("D. %s\n", question->choiceD);
    }
}

// DOUBLE DIP JOKERİ
void useDoubleDip(const struct Question* question, int* playerWinnings, int* currentLevel, int* correctAnswers) {
    printf("You have selected the Double Dip lifeline.\n");
    printf("You have two chances to answer the question.\n");

    printf("Enter your first choice (A/B/C/D): ");
    char firstChoice;
    scanf(" %c", &firstChoice);
    if(firstChoice >= 'a' && firstChoice <= 'z') firstChoice -= 32;

    if (firstChoice == question->correctChoice) {
        printf("Correct answer!\n");
        checkAnswer(question, firstChoice, playerWinnings, currentLevel, correctAnswers);
        return;
    } else {
        printf("Yanlış cevap! İkinci şansınızı kullanın: ");
        char secondChoice;
        scanf(" %c", &secondChoice);
        if(secondChoice >= 'a' && secondChoice <= 'z') secondChoice -= 32;
        checkAnswer(question, secondChoice, playerWinnings, currentLevel, correctAnswers);
    }
}

// CEVAP KONTROL (Senin checkAnswer mantığın)
void checkAnswer(const struct Question* question, char choice, int* playerWinnings, int* currentLevel, int* correctAnswers) {
    if (choice == 'Q') {
        printf("Oyuncu için oyunu sonlandır ve sonuçları toplam kazancını görüntüle:\n");
        *playerWinnings = calculateWinnings(*correctAnswers);
        printf("Toplam kazanç: %d TL\n", *playerWinnings);
        savePlayerWinnings(*playerWinnings);
        exit(0);
    }

    if (choice == question->correctChoice) {
        printf("Doğru Cevap\n");
        (*correctAnswers)++;
        *playerWinnings = calculateWinnings(*correctAnswers);
    } else {
        printf("Yanlış cevap. Oyun bitti.!\n");
        // Baraj mantığı (Senin kodundaki mantık)
        if (*currentLevel > 7) {
            *playerWinnings = 50000;
        } else if (*currentLevel > 2) {
            *playerWinnings = 5000;
        } else {
            *playerWinnings = 0;
        }
        printf("Toplam kazanç: %d TL\n", *playerWinnings);
        savePlayerWinnings(*playerWinnings);
        exit(0);
    }
}

// KAZANÇ KAYDETME
void savePlayerWinnings(int playerWinnings) {
    FILE* file = fopen("player_winnings.txt", "a");
    char playerName[50];

    printf("Lütfen isminizi girin: ");
    scanf("%s", playerName); // & isareti string icin gerekli degil

    if (file == NULL) {
        printf("Dosyayı yazmak için açarken hata oluştu.\n");
        return;
    }
    fprintf(file, "%s: %d TL\n", playerName, playerWinnings);
    fclose(file);
    printf("Kaydedildi.\n");
}

// RAPOR GÖSTERME
void showReport() {
    printf("Önceki yarışmacılar ve kazandıkları ödüller:\n");
    FILE* file = fopen("player_winnings.txt", "r");
    if (file == NULL) {
        printf("Daha önceki yarışmaları kaydeden dosya yok.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}
