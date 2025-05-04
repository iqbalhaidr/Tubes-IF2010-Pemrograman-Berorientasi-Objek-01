#include "../include/Dungeon.hpp"

#include <iostream>

//DONE
Dungeon::Dungeon(string rank, Mobloot &mobLoots, Items &items, Character &c) : prize() {
    this->rank = rank;
    helperSet(items, c);
    randomizeDoubleDungeon();
    generateChambers(mobLoots);
}

//DONE
Dungeon::~Dungeon() {
    for (Chamber *c : chambers) {
        delete c;
    }
    chambers.clear();
}

// DONE
void Dungeon::randomizeDoubleDungeon() {
    // Chance double dungeon 30%
    if (Randomizer::chance(0.3f)) {
        isDD = true;
        rewardExp *= 3;
        rewardGold *= 3;
    } else {
        isDD = false;
    }
}

//DONE
void Dungeon::helperSet(Items &items, Character &c) {
    if (rank == "S") {
        minLevel = 50;
        entryCost = 1000;
        rewardExp = 12000;
        rewardGold = 2000;
        penaltyExp = 1300;
        penaltyGold = 500;
        bonusItem = items.getItem("DRA");
    } else if (rank == "A") {
        minLevel = 35;
        entryCost = 500;
        rewardExp = 5000;
        rewardGold = 1300;
        penaltyExp = 850;
        penaltyGold = 300;
        bonusItem = items.getItem("PRM");
    } else if (rank == "B") {
        minLevel = 25;
        entryCost = 300;
        rewardExp = 2000;
        rewardGold = 900;
        penaltyExp = 650;
        penaltyGold = 200;
        bonusItem = items.getItem("PDF");
    } else if (rank == "C") {
        minLevel = 20;
        entryCost = 150;
        rewardExp = 1300;
        rewardGold = 650;
        penaltyExp = 400;
        penaltyGold = 125;
        bonusItem = items.getItem("PAT");
    } else if (rank == "D") {
        minLevel = 10;
        entryCost = 0;
        rewardExp = 800;
        rewardGold = 350;
        penaltyExp = 250;
        penaltyGold = 80;
        bonusItem = items.getItem("PSN");
    } else if (rank == "E") {
        minLevel = 0;
        entryCost = 0;
        rewardExp = 300;
        rewardGold = 200;
        penaltyExp = 100;
        penaltyGold = 50;
        bonusItem = items.getItem("HLT");
    } else if (rank == "SPECIAL") {
        minLevel = 0;
        entryCost = 0;
        rewardExp = int(int(pow(c.getLevel(), 1.5)) * int(pow(100, 1 + 0.005 * c.getLevel())) * 0.3);
        rewardGold = 10000;
        penaltyExp = 100 * c.getLevel();
        penaltyGold = 300;
        bonusItem = items.getItem("EXC");
    }
}

void Dungeon::generateChambers(Mobloot &mobLoots) {
    if (rank == "S") {
        totalChambers = 6;
        int minMobLevel = isDD ? 100 : 50;
        int maxMobLevel = isDD ? 200 : 100;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "A") {
        totalChambers = 5;
        int minMobLevel = isDD ? 60 : 30;
        int maxMobLevel = isDD ? 140 : 70;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "B") {
        totalChambers = 4;
        int minMobLevel = isDD ? 40 : 20;
        int maxMobLevel = isDD ? 100 : 50;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "C") {
        totalChambers = 3;
        int minMobLevel = isDD ? 20 : 10;
        int maxMobLevel = isDD ? 70 : 35;

        for (int i = 0; i < totalChambers - 1; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
        chambers.push_back(new Chamber(true, minMobLevel, maxMobLevel, mobLoots));
    } else if (rank == "D") {
        totalChambers = 2;
        int minMobLevel = isDD ? 0 : 0;
        int maxMobLevel = isDD ? 50 : 25;

        for (int i = 0; i < totalChambers; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
    } else if (rank == "E") {
        totalChambers = 1;
        int minMobLevel = isDD ? 0 : 0;
        int maxMobLevel = isDD ? 20 : 10;

        for (int i = 0; i < totalChambers; i++) {
            chambers.push_back(new Chamber(false, minMobLevel, maxMobLevel, mobLoots));
        }
    } else if (rank == "SPECIAL") {
        totalChambers = 100;

        for (int i = 0; i < totalChambers - 1; i++) {
            int curLevel = isDD ? (i + 1) * 2 : (i + 1);
            chambers.push_back(new Chamber(false, curLevel, curLevel, mobLoots));
        }
        int curLevel = isDD ? 200 : 100;
        chambers.push_back(new Chamber(true, curLevel, curLevel, mobLoots));
    }
}

void Dungeon::start(Character &c, Inventory &inv, Items &items) {
    if (c.getLevel() < minLevel) {
        std::cout << "Level karakter tidak mencukupi untuk memasuki dungeon ini." << std::endl;
        return;
    }

    if (c.getGold() < entryCost) {
        std::cout << "Karakter tidak memiliki cukup gold untuk memasuki dungeon ini." << std::endl;
        return;
    }
    c.setGold(c.getGold() - entryCost);

    welcomeMessage();
    bool neverLose = true;
    int ctr = 0;

    while (neverLose && ctr < totalChambers) {
        std::cout << "\e[1;1H\e[2J";  // Clear console
        std::cout << "Entering chamber " << ctr + 1 << " of " << totalChambers << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "\e[1;1H\e[2J";  // Clear console

        bool result = chambers[ctr]->battle(c, inv, this->prize, items);
        // std::cout << "[DEBUG] attackDamage keluar chamber: " << c.getAttackDamage() << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        neverLose = result;
        ctr++;
    }

    if (neverLose) {
        prize.addExp(rewardExp);
        prize.addGold(rewardGold);
        prize.addItem(bonusItem, 1);
        prize.giveTo(&c, &inv);
        winningMessage();

        std::cout << "Final Reward\n";
        prize.displayInfo();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "\e[1;1H\e[2J";  // Clear console
    } else {
        substractExp(&c, penaltyExp);
        substractGold(&c, penaltyGold);
        if (isDD) {
            prize.giveTo(&inv);
        }
        losingMessage();

        std::cout << "Final Reward\n";
        prize.displayInfo();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "\e[1;1H\e[2J";  // Clear console
    }

    c.reset();
}

void Dungeon::displayInfo() {
    std::cout << "Dungeon Rank: " << rank << std::endl;
    std::cout << "Total Chambers: " << totalChambers << std::endl;
    std::cout << "Entry Cost: " << entryCost << std::endl;
    std::cout << "Minimum Level: " << minLevel << std::endl;
    std::cout << "Reward Exp: " << rewardExp << std::endl;
    std::cout << "Reward Gold: " << rewardGold << std::endl;
    std::cout << "isDD: " << (isDD ? "Yes" : "No") << std::endl;
    std::cout << "Penalty Exp: " << penaltyExp << std::endl;
    std::cout << "Penalty Gold: " << penaltyGold << std::endl;
    std::cout << "Prize: " << std::endl;
    prize.displayInfo();
    std::cout << "Bonus Item: " << (bonusItem ? bonusItem->getName() : "None") << std::endl;
    std::cout << "Chambers:" << std::endl;
    for (int i = 0; i < totalChambers; ++i) {
        std::cout << "  Chamber " << i + 1 << ":" << std::endl;
        chambers[i]->displayInfo();
    }
}

void Dungeon::substractExp(Character *c, int penaltyExp) {
    if (penaltyExp > c->getExp()) {
        penaltyExp = c->getExp();
    }
    c->setExp(c->getExp() - penaltyExp);
}

void Dungeon::substractGold(Character *c, int penaltyGold) {
    if (penaltyGold > c->getGold()) {
        penaltyGold = c->getGold();
    }
    c->setGold(c->getGold() - penaltyGold);
}

void Dungeon::typeEffect(const std::string &text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

void Dungeon::welcomeMessage() {
    std::cout << "\e[1;1H\e[2J";  // Clear console
    std::map<string, string> dungeonNames = {
        {"S", "Sepulcher of the Silent King"},
        {"A", "Abyssal Vault"},
        {"B", "Bloodhollow Bastion"},
        {"C", "Crimson Hollow"},
        {"D", "Driftshade Hollow"},
        {"E", "Eldermoss Grotto"},
        {"SPECIAL", "The Special Requiem of Forgotten Gods"}};

    std::string kalimat =
        "Kau berdiri di hadapan gerbang kuno yang mengarah ke " + dungeonNames[rank] +
        ", tempat di mana cahaya dunia \nluar sirna, dan hanya keberanianmu yang jadi penerang.\n\n"
        "Di dalamnya tersebar " + to_string(totalChambers) + " chamber, masing-masing menyimpan "
        "monster yang akan menguji \nkekuatan, akal, dan nyalimu.\n\n";
    
    if (isDD) {
        kalimat += 
            "Namun kekuatan purba telah bangkit. Ini adalah Double Dungeon, "
            "di mana musuh menjadi dua kali lebih \nkuat, jebakan lebih mematikan, "
            "dan ganjaran—tiga kali lipat lebih besar. Hanya sedikit yang pernah \n"
            "kembali dari kegelapan seperti ini.\n\n";
    } else {
        kalimat += 
            "Tak ada yang pasti di dalamnya, kecuali satu hal: mereka yang masuk "
            "tak selalu keluar.\n\n";
    }

    kalimat += 
    "Langkahkan kakimu, dan tulislah kisahmu—sebagai pahlawan yang menaklukkan kegelapan, "
    "atau satu \nlagi jiwa yang hilang dalam diam.\n\n";

    typeEffect(kalimat, 50);
    std::cout << "[PRESS ENTER TO CONTINUE]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\e[1;1H\e[2J"; //Clear console
}

void Dungeon::winningMessage() {
    std::cout << "\e[1;1H\e[2J";  // Clear console
    std::string kalimat =
        "Dengan nafas tersisa dan langkah berat, kau keluar dari bayang-bayang yang hampir menelan segalanya. \n"
        "Chamber terakhir telah kau taklukkan, dan rahasia kini milikmu.\n\n"
        "Tak semua luka terlihat, dan tak semua kemenangan bersih. Tapi kau bertahan—dan di dunia "
        "yang kejam ini, \nitu sudah lebih dari cukup.\n\n"
        "Cahaya menyambutmu kembali. Dan bersama cahaya itu, datanglah ganjaran: harta, peninggalan "
        "kuno,\ndan kekuatan yang hanya dimiliki mereka yang selamat.\n\n"
        "Untuk sekarang… kau menang. Dunia akan mengingatnya.\n\n";
    
    typeEffect(kalimat, 50);
    std::cout << "[PRESS ENTER TO CONTINUE]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\e[1;1H\e[2J"; //Clear console
}

void Dungeon::losingMessage() {
    std::cout << "\e[1;1H\e[2J";  // Clear console
    std::string kalimat = 
        "Langkahmu terhenti disini. Chamber itu bukan sekadar ruang ujian, \nmelainkan ruang penghakiman.\n\n"
        "Tak ada sorak sorai, tak ada yang menyaksikan akhir perjalananmu—hanya dinding bisu \ndan bayangan yang kembali diam.\n\n"
        "Kegagalan di tempat ini tak datang tanpa harga: sebagian kekayaanmu hilang, waktu \ntak bisa kau ambil kembali, dan namamu… untuk sementara terhapus dari lagu \nkemenangan.\n\n"
        "Di tempat ini, keberanian saja tidak cukup. Tapi jangan khawatir. Dungeon ini tak \npernah kekurangan pahlawan baru…\n\n";

    typeEffect(kalimat, 50);
    std::cout << "[PRESS ENTER TO CONTINUE]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\e[1;1H\e[2J"; //Clear console
}