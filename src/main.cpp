#include "../include/Player.hpp"

void typeEffect(const std::string &text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}



int main(){
    Characters* allChar = nullptr;
    Items* itemMap = nullptr;
    Shop* shop = nullptr;
    Player* p1 = nullptr;
    Mobloot* mobsLoot = nullptr;
    Inventory* inv = nullptr;



    std::vector<std::string> required_files = {
        "characters.txt",
        "item.txt",
        "shop.txt",
        "backpack.txt",
        "equipment.txt"
    };

    std::string folder_path;

    while (true) {
        std::cout << "Masukkan path folder: ";
        std::getline(std::cin, folder_path);

        try {
            fs::path folder = fs::path(folder_path).lexically_normal();
            if (folder_path.back() != '/' && folder_path.back() != '\\') {
                folder /= ""; 
            }
            std::cout << folder << "\n";

            if (!fs::exists(folder)) {
                throw InputOutputException("Path tidak ditemukan.");
            }

            if (!fs::is_directory(folder)) {
                throw InputOutputException("Path bukan direktori.");
            }

            std::vector<std::string> missing_files;
            for (const auto& filename : required_files) {
                fs::path fullpath = folder / filename;
                if (!fs::exists(fullpath)) {
                    missing_files.push_back(filename);
                }
            }

            if (!missing_files.empty()) {
                std::string error_msg = "File berikut tidak ditemukan di folder:\n";
                for (const auto& file : missing_files) {
                    error_msg += "- " + file + "\n";
                }
                throw InputOutputException(error_msg);
            }
            try {

                allChar = new Characters(folder_path);
                itemMap = new Items(Items::createFromDirectory(folder_path)); 
                shop = new Shop(folder_path);
                mobsLoot = new Mobloot(folder_path, *itemMap);
                inv = new Inventory(Inventory::loadInventory(folder_path, *itemMap));
                
            } catch (const std::exception& e) {
                // Cleanup jika ada exception
                delete allChar;
                delete shop;
                delete mobsLoot;
                delete itemMap;
                delete inv;
                throw; 
            }
            break;

        } 
        catch (const std::exception& e) {
            std::cerr << "Terjadi kesalahan: " << e.what() << std::endl;
        }
    }



    bool end = false;
    bool characterCreated = false;

    while(!end){
        //pilih char    
        if(!characterCreated){
            std::string kalimat = "Dunia ini… bukan dunia yang kau kenal\n"
            "Di sini, waktu berputar tak menentu, dan takdir ditulis ulang oleh tangan-tangan berani.\n"
            "Jiwa-jiwa lama berbisik dari balik kabut abadi, meminta kesempatan kedua…\n"
            "Sementara yang baru, menunggu untuk dilahirkan dalam legenda.\n"
            "Apakah kau jiwa yang telah hidup sebelumnya, atau jiwa baru yang memanggil petualangan pertama?\n\n";

            typeEffect(kalimat,50);
            std::cout << "\nBuat character baru:\n";
            std::cout << "1. Ya \n";
            std::cout << "2. Tidak \n";
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
                std::cout << "Silahkan masukkan tipe yang anda inginkan (1-5): " << std::endl;
                bool isValid2 = false;
                std::string name;
                while (!isValid2) {
                    std::cin >> optPlay;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Masukan tidak valid." << std::endl;
                        std::cout << "Silahkan masukkan tipe yang anda inginkan (1-5): " << std::endl;
                    } else if (optPlay >= 1 && optPlay <= 5) {
                        isValid2 = true;
                        std::cout << std::endl << std::endl;
                    } else {
                        std::cout << "Masukan tidak valid." << std::endl;
                    }
                }

                allChar->displayAvailableCharacters();
                while (true) {
                    std::cout << "Silahkan Masukkan nama character Anda: ";
                    std::cin >> name;
                
                    try {
                        if (!allChar->searchCharacter(name)) {
                            p1 = new Player(folder_path, name, *itemMap, *allChar, optPlay);
                            allChar->addCharacters(p1->getChar());
                            std::cout << "Pembuatan karakter berhasil!" << std::endl;
                        }
                        else{
                            throw CharactersError("Jangan memasukkan nama character yang sudah pernah ada");
                        }

                        break; 
                
                    } catch (const std::exception& e) {
                        std::cerr << "Gagal membuat karakter: " << e.what() << std::endl;
                        std::cerr << "Silakan coba lagi." << std::endl;
                    }
                }
            } 
            else{
                allChar->displayAvailableCharacters();
                std::cout << "Silahkan pilih karakter Anda: ";
                
                std::string chosenName;
                while (true) {
                    std::cin >> chosenName;
                
                    if (allChar->searchCharacter(chosenName)) {
                        std::cout << "Karakter '" << chosenName << "' berhasil dipilih!" << std::endl;
                        break;
                    } else {
                        std::cout << "Karakter tidak ditemukan. Silakan masukkan nama karakter yang valid: ";
                    }
                }
                p1 = new Player(folder_path, chosenName, *itemMap, *allChar, 0);
            }
            characterCreated = true;
            std::cout << "Selamat datang jiwa yang tersesat" <<std::endl;
        }


        bool isValid3 = false;
        int opt;


        while (!isValid3) {
            std::cout << "Silahkan pilih tujuan Anda" <<std::endl;
            std::cout << "1. Player Status " <<std::endl;
            std::cout << "2. Inventory " <<std::endl;
            std::cout << "3. Shop " <<std::endl;
            std::cout << "4. Dungeon "<<std::endl;
            std::cout << "5. Gunung Myoboku (upgrade skil) "<<std::endl;
            std::cout << "6. Turu (save) "<<std::endl;
            std::cout << "7. Keluar "<<std::endl;
            std::cout << "Silahkan Masukkan Angka (1-5):" ;
            std::cin >> opt;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Masukan tidak valid." << std::endl;
            } else if (opt >= 1 && opt <= 7) {
                if(opt==1){
                    p1->getChar()->displayCharacter();
                    break;
                }
                else if(opt==2){
                    std::cout << "\n\n";
                    std::cout << "\e[1;1H\e[2J"; //Clear console
                    std::cout << "Selamat datang di menu Inventory!\n";
                    while (true) {
                        std::cout << "\e[1;1H\e[2J"; //Clear console
                        std::cout << "1. Equip item\n";
                        std::cout << "2. Unequip item\n";
                        std::cout << "3. Lihat tas\n";
                        std::cout << "4. Lihat equipment\n";
                        std::cout << "5. Keluar\n";
                
                        int optInvent;
                        bool isValid = false;
                        while (!isValid) {
                            std::cout << "Pilih opsi: ";
                            std::cin >> optInvent;
                
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                                '\n');
                                std::cout << "Masukan tidak valid." << std::endl;
                            } else if (optInvent >= 1 && optInvent <= 5) {
                                isValid = true;
                            } else {
                                std::cout << "Masukan tidak valid." << std::endl;
                            }
                        }
                        if(optInvent==1){
                            std::string itemId;
                            std::cout << "Pilih dan ketik ID Item yang ingin di-equip (contoh: BLD): ";
                            cin>>itemId;
                            std::string equipSlot;
                            
                            while (true) {
                                std::cout << "Pilih dan ketik slot yang ingin di-equip \n"
                                <<"(WEAPON/ARMOR_HEAD/ARMOR_BODY/ARMOR_FOOT/PENDANT/KELUAR): ";
                                cin>>equipSlot;

                                if (equipSlot == "WEAPON" || equipSlot == "ARMOR_HEAD" || equipSlot == "ARMOR_BODY" ||
                                    equipSlot == "ARMOR_FOOT" || equipSlot == "PENDANT" || equipSlot == "KELUAR") {
                                    break;
                                } else {
                                    std::cout << "Input tidak valid." << std::endl;
                                }
                            }
                            if(!(equipSlot=="KELUAR")){
                                p1->playerEquip(itemId, equipSlot);
                            }
                        }
                        else if(optInvent==2){
                            bool isInputTrue = false;
                            std::string slot;
                            while (!isInputTrue) {
                                std::cout << "Pilih dan ketik slot yang ingin di-un-equip \n"
                                <<"(WEAPON/ARMOR_HEAD/ARMOR_BODY/ARMOR_FOOT/PENDANT/KELUAR): ";
                                std::cin >> slot;

                                if (slot == "WEAPON" || slot == "ARMOR_HEAD" || slot == "ARMOR_BODY" ||
                                    slot == "ARMOR_FOOT" || slot == "PENDANT" || slot == "KELUAR") {
                                    isInputTrue = true;
                                } else {
                                    std::cout << "Input tidak valid." << std::endl;
                                }
                            }

                            if (slot == "WEAPON") {
                                p1->playerUnequip(slot);
                                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                            } else if (slot == "ARMOR_HEAD") {
                                p1->playerUnequip(slot);
                                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                                // std::cout << "Berhasil meng-un-equip armor head" << std::endl;
                            } else if (slot == "ARMOR_BODY") {
                                p1->playerUnequip(slot);
                                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                                // std::cout << "Berhasil meng-un-equip armor body" << std::endl;
                            } else if (slot == "ARMOR_FOOT") {
                                p1->playerUnequip(slot);
                                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                                // std::cout << "Berhasil meng-un-equip armor foot" << std::endl;
                            } else if (slot == "PENDANT") {
                                p1->playerUnequip(slot);
                                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                                // std::cout << "Berhasil meng-un-equip pendant" << std::endl;
                            } else if (slot == "KELUAR") {}
                        }
                        else if(optInvent==3){
                            p1->showInventory(true);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                        }
                        else if(optInvent==4){
                            std::cout << "\n\n";
                            p1->showInventory(false);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_TIME));
                        }
                        else if(optInvent==5){
                            break;
                        }
 
                    }

                    std::cout << "\n\n";
                    break;
                }
                else if(opt==3){
                    p1->goToShop(*shop);
                    break;
                }
                else if(opt==4){
                    p1->goToDungeon(*mobsLoot, *itemMap);
                    break;
                }
                else if(opt==5){
                    std::string skillName;
                    p1->getChar()->displayAvailableSkillUpgrades();
                    cout<<"Masukkan Pilihan Anda: ";
                    cin>>skillName;
                    break;
                    while (true) {
                        cout<<"Masukkan Pilihan Anda: ";
                        cin>>skillName;
                        try {
                            p1->getChar()->upgradeSkill(skillName);
                        } catch(const InvalidSkill& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        } catch(const MasteryCostNotEnough& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }
                    }
                }
                else if(opt==6){
                    //input user
                    // std::string path;
                    // while (true) {
                    //     std::cout << "Silahkan masukkan path menuju data yang akan disimpan: ";
                    //     std::cin >> path;
                    
                    //     try {
                    //         if (!std::filesystem::exists(path)) {
                    //             throw InputOutputException("Path tidak ditemukan.");
                    //         }
                    
                    //         if (!std::filesystem::is_directory(path)) {
                    //             throw InputOutputException("Path yang dimasukkan bukan folder.");
                    //         }
                    //         break;
                    
                    //     } catch (const std::exception& e) {
                    //         std::cerr << "Terjadi kesalahan: " << e.what() << std::endl;
                    //         std::cerr << "Silakan coba lagi.\n";
                    //     }
                    // }

                    //sementara
                    p1->getInv()->saveInventory("../datadump/");
                    allChar->save("../datadump/");
                    itemMap->save("../datadump/");
                    shop->saveShop("../datadump/");
                    break;
                }
                else if (opt==7){
                    std::string penutup = 
                        "\nLangkahmu mungkin terhenti di sini…\n"
                        "Namun dunia ini tetap berputar dalam keheningan dan rahasia.\n"
                        "Jejakmu terukir di antara legenda, bersama tawa, luka, dan keberanianmu.\n"
                        "Suatu saat, mungkin kau akan kembali—atau mungkin jiwa lain akan meneruskan kisahmu.\n"
                        "Untuk sekarang… istirahatlah, penjelajah.\n"
                        "Kabut akan menyelimuti lagi, dan dunia ini… akan menunggu.\n";
                    typeEffect(penutup,50);
                    end = true;
                    isValid3 = true;
                }

            } else {
                std::cout << "Masukan tidak valid." << std::endl;
            }
        }

    }
    

    return 0;
}