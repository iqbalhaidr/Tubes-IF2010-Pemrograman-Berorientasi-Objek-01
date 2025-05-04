#include "../include/Player.hpp"

void typeEffect(const std::string &text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}



int main(){
    Characters allChar("../data/");
    Items itemMap = Items::createFromDirectory("../data/");
    Shop shop("../data/");
    Player* p1;
    Mobloot mobsLoot("../data/", itemMap);

    bool end = false;
    bool characterCreated = false;

    while(!end){
        //pilih char
        if(!characterCreated){
            std::string kalimat = "Dunia ini… bukan dunia yang kau kenal"
            "Di sini, waktu berputar tak menentu, dan takdir ditulis ulang oleh tangan-tangan berani."
            "Jiwa-jiwa lama berbisik dari balik kabut abadi, meminta kesempatan kedua…"
            "Sementara yang baru, menunggu untuk dilahirkan dalam legenda."
            "Apakah kau jiwa yang telah hidup sebelumnya, atau jiwa baru yang memanggil petualangan pertama?";

            typeEffect(kalimat,50);
            std::cout << "\nBuat character baru:";
            std::cout << "1. Ya ";
            std::cout << "2. Tidak ";
            bool isValid = false;
            int opt;
            while (!isValid) {
                std::cin >> opt;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Masukan tidak valid." << std::endl;
                } else if (opt >= 1 && opt <= 2) {
                    isValid = true;
                } else {
                    std::cout << "Masukan tidak valid." << std::endl;
                }
            }

            int optPlay;
            if(opt == 1){
                std::cout << "Silahkan pilih tipe karakter Anda" << std::endl;
                std::cout << "1. Berserker " <<std::endl;
                std::cout << "2. Fighter " <<std::endl;
                std::cout << "3. Mage "<<std::endl;
                std::cout << "4. Necromancer "<<std::endl;
                std::cout << "5. Assassin "<<std::endl;

                bool isValid2 = false;
                std::string name;
                while (!isValid2) {
                    std::cin >> optPlay;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Masukan tidak valid." << std::endl;
                    } else if (optPlay >= 1 && optPlay <= 5) {
                        cin>>name;
                        isValid2 = true;
                    } else {
                        std::cout << "Masukan tidak valid." << std::endl;
                    }
                }
                p1 = new Player("../data/", name, itemMap, allChar, optPlay);
            } 
            else{
                p1 = new Player("../data/", "Thorgar", itemMap, allChar, 0);
            }
            characterCreated = true;
            std::cout << "Selamat datang jiwa yang tersesat" <<std::endl;
        }


        bool isValid3 = false;
        int opt;
        std::cout << "Silahkan pilih tujuan Anda" <<std::endl;
        std::cout << "1. Shop " <<std::endl;
        std::cout << "2. Dungeon "<<std::endl;
        std::cout << "3. Gunung Myoboku (upgrade skil) "<<std::endl;
        std::cout << "4. Turu (save) "<<std::endl;

        while (!isValid3) {
            std::cin >> opt;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Masukan tidak valid." << std::endl;
            } else if (opt >= 1 && opt <= 4) {
                if(opt==1){
                    p1->goToShop(shop);
                }
                else if(opt==2){
                    p1->goToDungeon(mobsLoot, itemMap);
                }
                else if(opt==3){
                    std::string skillName;
                    p1->getChar()->displayAvailableSkillUpgrades();
                    cout<<"Masukkan Pilihan Anda\n";
                    cin>>skillName;
                    p1->getChar()->UpgradeSkill(skillName);
                }
                else{
                    //input user
                    std::string path;
                    cout<<"Silahkan masukkan path menuju data yang akan disimpan";
                    cin>>path;
                    allChar.save("../datadump/");
                    itemMap.save("../datadump/");
                    shop.saveShop("../datadump/");

                }
                isValid3 = true;
            } else {
                std::cout << "Masukan tidak valid." << std::endl;
            }
        }

    }
    

    return 0;
}