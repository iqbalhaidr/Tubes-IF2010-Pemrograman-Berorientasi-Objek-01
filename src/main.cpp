// #include "../include/Player.hpp"

// void typeEffect(const std::string &text, int delayMs) {
//     for (char c : text) {
//         std::cout << c << std::flush;
//         std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
//     }
// }



// int main(){
//     std::vector<std::string> required_files = {
//         "characters.txt",
//         "item.txt",
//         "shop.txt",
//         "backpack.txt",
//         "equipment.txt"
//     };

//     std::string folder_path;

//     while (true) {
//         std::cout << "Masukkan path folder: ";
//         std::getline(std::cin, folder_path);

//         try {
//             fs::path folder = fs::path(folder_path).lexically_normal();
//             if (folder_path.back() != '/' && folder_path.back() != '\\') {
//                 folder /= ""; 
//             }
//             std::cout << folder << "\n";

//             if (!fs::exists(folder)) {
//                 throw InputOutputException("Path tidak ditemukan.");
//             }

//             if (!fs::is_directory(folder)) {
//                 throw InputOutputException("Path bukan direktori.");
//             }

//             std::vector<std::string> missing_files;
//             for (const auto& filename : required_files) {
//                 fs::path fullpath = folder / filename;
//                 if (!fs::exists(fullpath)) {
//                     missing_files.push_back(filename);
//                 }
//             }

//             if (!missing_files.empty()) {
//                 std::string error_msg = "File berikut tidak ditemukan di folder:\n";
//                 for (const auto& file : missing_files) {
//                     error_msg += "- " + file + "\n";
//                 }
//                 throw InputOutputException(error_msg);
//             }

//             std::cout << "Folder valid dan semua file ditemukan!" << std::endl;
//             break;

//         } catch (const std::exception& e) {
//             std::cerr << "Terjadi kesalahan: " << e.what() << std::endl;
//         }
//     }


//     Characters allChar(folder_path);
//     Items itemMap = Items::createFromDirectory(folder_path);
//     Shop shop(folder_path);
//     Player* p1;
//     Mobloot mobsLoot(folder_path, itemMap);

//     bool end = false;
//     bool characterCreated = false;

//     while(!end){
//         //pilih char    
//         if(!characterCreated){
//             std::string kalimat = "Dunia ini… bukan dunia yang kau kenal\n"
//             "Di sini, waktu berputar tak menentu, dan takdir ditulis ulang oleh tangan-tangan berani.\n"
//             "Jiwa-jiwa lama berbisik dari balik kabut abadi, meminta kesempatan kedua…\n"
//             "Sementara yang baru, menunggu untuk dilahirkan dalam legenda.\n"
//             "Apakah kau jiwa yang telah hidup sebelumnya, atau jiwa baru yang memanggil petualangan pertama?\n\n";

//             typeEffect(kalimat,50);
//             std::cout << "\nBuat character baru:\n";
//             std::cout << "1. Ya \n";
//             std::cout << "2. Tidak \n";
//             bool isValid = false;
//             int opt;
//             while (!isValid) {
//                 std::cin >> opt;
//                 if (std::cin.fail()) {
//                     std::cin.clear();
//                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                     std::cout << "Masukan tidak valid." << std::endl;
//                 } else if (opt >= 1 && opt <= 2) {
//                     isValid = true;
//                 } else {
//                     std::cout << "Masukan tidak valid." << std::endl;
//                 }
//             }

//             int optPlay;
//             if(opt == 1){
//                 std::cout << "Silahkan pilih tipe karakter Anda" << std::endl;
//                 std::cout << "1. Berserker " <<std::endl;
//                 std::cout << "2. Fighter " <<std::endl;
//                 std::cout << "3. Mage "<<std::endl;
//                 std::cout << "4. Necromancer "<<std::endl;
//                 std::cout << "5. Assassin "<<std::endl;
//                 std::cout << "Silahkan masukkan tipe yang anda inginkan (1-5): " << std::endl;
//                 bool isValid2 = false;
//                 std::string name;
//                 while (!isValid2) {
//                     std::cin >> optPlay;
//                     if (std::cin.fail()) {
//                         std::cin.clear();
//                         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                         std::cout << "Masukan tidak valid." << std::endl;
//                         std::cout << "Silahkan masukkan tipe yang anda inginkan (1-5): " << std::endl;
//                     } else if (optPlay >= 1 && optPlay <= 5) {
//                         isValid2 = true;
//                     } else {
//                         std::cout << "Masukan tidak valid." << std::endl;
//                     }
//                 }
                
//                 while (true) {
//                     std::cout << "Silahkan Masukkan nama character Anda: ";
//                     std::cin >> name;
                
//                     try {
//                         p1 = new Player(folder_path, name, itemMap, allChar, optPlay);
                
//                         std::cout << "Pembuatan karakter berhasil!" << std::endl;
//                         break; 
                
//                     } catch (const std::exception& e) {
//                         std::cerr << "Gagal membuat karakter: " << e.what() << std::endl;
//                         std::cerr << "Silakan coba lagi." << std::endl;
//                     }
//                 }
//             } 
//             else{
//                 p1->getChar()->displayCharacter();
//                 std::cout << "Silahkan pilih karakter Anda: ";
                
//                 std::string chosenName;
//                 while (true) {
//                     std::cin >> chosenName;
                
//                     if (allChar.searchCharacter(chosenName)) {
//                         std::cout << "Karakter '" << chosenName << "' berhasil dipilih!" << std::endl;
//                         break;
//                     } else {
//                         std::cout << "Karakter tidak ditemukan. Silakan masukkan nama karakter yang valid: ";
//                     }
//                 }
//                 p1 = new Player(folder_path, chosenName, itemMap, allChar, 0);
//             }
//             characterCreated = true;
//             std::cout << "Selamat datang jiwa yang tersesat" <<std::endl;
//         }


//         bool isValid3 = false;
//         int opt;
//         std::cout << "Silahkan pilih tujuan Anda" <<std::endl;
//         std::cout << "1. Shop " <<std::endl;
//         std::cout << "2. Dungeon "<<std::endl;
//         std::cout << "3. Gunung Myoboku (upgrade skil) "<<std::endl;
//         std::cout << "4. Turu (save) "<<std::endl;
//         std::cout << "5. Keluar "<<std::endl;

//         while (!isValid3) {
//             std::cin >> opt;
//             if (std::cin.fail()) {
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 std::cout << "Masukan tidak valid." << std::endl;
//             } else if (opt >= 1 && opt <= 4) {
//                 if(opt==1){
//                     p1->goToShop(shop);
//                 }
//                 else if(opt==2){
//                     p1->goToDungeon(mobsLoot, itemMap);
//                 }
//                 else if(opt==3){
//                     std::string skillName;
//                     p1->getChar()->displayAvailableSkillUpgrades();
//                     while (true) {
//                         cout<<"Masukkan Pilihan Anda\n";
//                         cin>>skillName;
//                         try {
//                             p1->getChar()->upgradeSkill(skillName);
//                         } catch(const InvalidSkill& e) {
//                             std::cerr << "Error: " << e.what() << std::endl;
//                         } catch(const MasteryCostNotEnough& e) {
//                             std::cerr << "Error: " << e.what() << std::endl;
//                         }
//                     }
//                 }
//                 else if(opt==4){
//                     //input user
//                     // std::string path;
//                     // while (true) {
//                     //     std::cout << "Silahkan masukkan path menuju data yang akan disimpan: ";
//                     //     std::cin >> path;
                    
//                     //     try {
//                     //         if (!std::filesystem::exists(path)) {
//                     //             throw InputOutputException("Path tidak ditemukan.");
//                     //         }
                    
//                     //         if (!std::filesystem::is_directory(path)) {
//                     //             throw InputOutputException("Path yang dimasukkan bukan folder.");
//                     //         }
//                     //         break;
                    
//                     //     } catch (const std::exception& e) {
//                     //         std::cerr << "Terjadi kesalahan: " << e.what() << std::endl;
//                     //         std::cerr << "Silakan coba lagi.\n";
//                     //     }
//                     // }

//                     //sementara
//                     p1->getInv()->saveInventory("../datadump/");
//                     allChar.save("../datadump/");
//                     itemMap.save("../datadump/");
//                     shop.saveShop("../datadump/");

//                 }
//                 else{
//                     std::string penutup = 
//                         "\nLangkahmu mungkin terhenti di sini…\n"
//                         "Namun dunia ini tetap berputar dalam keheningan dan rahasia.\n"
//                         "Jejakmu terukir di antara legenda, bersama tawa, luka, dan keberanianmu.\n"
//                         "Suatu saat, mungkin kau akan kembali—atau mungkin jiwa lain akan meneruskan kisahmu.\n"
//                         "Untuk sekarang… istirahatlah, penjelajah.\n"
//                         "Kabut akan menyelimuti lagi, dan dunia ini… akan menunggu.\n";
//                     typeEffect(penutup,50);
//                     isValid3 = true;
//                 }

//             } else {
//                 std::cout << "Masukan tidak valid." << std::endl;
//             }
//         }

//     }
    

//     return 0;
// }