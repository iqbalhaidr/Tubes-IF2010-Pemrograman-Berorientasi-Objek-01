// #include <iostream>
// #include <vector>
// #include <chrono>
// #include <thread>
// #ifdef _WIN32
// #include <windows.h>
// #else
// #include <unistd.h>
// #endif

// using namespace std;

// void clearScreen() {
// #ifdef _WIN32
//     system("cls");
// #else
//     system("clear");
// #endif
// }

// vector<string> shop = {
//     "      ______________________",
//     "      |\\\\\\\\\\\\||||||||//////|",
//     "      |   ___    SHOP    ___ |",
//     "      |  |___|          |___||",
//     "      |  |_|_|   __     |_|_||",
//     "     _|_______________ ______|_",
//     "    |                   |      |",
//     "    |   [ ]       [ ]   | [ ]  |",
//     "    |                   |      |",
//     "    |___|_________|_____|______|"
// };

// int main() {
//     const int totalFrames = 25;  // Reduced from 25 to stop earlier
//     const int stickmanLine = shop.size() - 2;
//     const int shopIndent = 25;  // Fixed shop position
//     const int stopDistance = 3; // Distance from shop where stickman stops

//     for (int frame = 0; frame <= totalFrames; ++frame) {
//         clearScreen();

//         // Calculate position with stop distance
//         int currentPos = min(frame, shopIndent - stopDistance);

//         for (size_t i = 0; i < shop.size(); ++i) {
//             string line;

//             // Render stickman on the appropriate line
//             if (i == stickmanLine - 1)
//                 line = string(currentPos, ' ') + " o ";
//             else if (i == stickmanLine)
//                 line = string(currentPos, ' ') + "/|\\";
//             else if (i == stickmanLine + 1)
//                 line = string(currentPos, ' ') + "/ \\";
//             else
//                 line = string(currentPos, ' ');  // Empty space for other lines

//             // Add shop at fixed position
//             while (line.length() < shopIndent)
//                 line += ' ';  // Padding to shop position

//             line += shop[i];

//             cout << line << endl;
//         }

//         this_thread::sleep_for(chrono::milliseconds(150));
//     }

//     cout << "\n>> Selamat datang di SHOP! <<\n";
//     return 0;
// }

#include "animation.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void Animation::clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

std::vector<std::string> Animation :: getAnimationFrames() {
    return {
        
        R"(











	          _        <\ 
	          \`\     ;`| 
	     ,    |  \   ; )| 
	    /|    /   `-´ / | 
	    | \--´  ´"` .´ || 
	    |  `,__  . ´!  || 
	    | : '    '     || 
	               |      )",
                      
                      
                      
                      
                      
	R"(   
    
              _        <\ 
	          \`\     ;`| 
	     ,    |  \   ; )| 
	    /|    /   `-´ / | 
	    | \--´  ´"` .´ || 
	    |  `,__  . ´!  || 
	    | : '    '     || 
	    | |  ,  .      '| 
	   /!    |  !  .    | 
	  /      |     |   || 
	 .       '     |   |' 
	 |             '   |  
	 |                 '  
	 |              .     
	 |              |     
	                |        )",  
                        
                        
                        
	R"( 
             _             
	          \`\      .^`) 
	     ,    |  \   ;´ //  
	    /|    /   `-´ .´/   
	    | \--´  ´"` .´ /    
	     \ `.____.-´  .     
	      \           '     
	    .´ `-.__.´   /      
	   /           .´       
	  /           /         
	 .           .          
	 |           |          
	 |           '          
	 |            \         
	 '             \        
	  \             .       
	   .            |       
	   |            |     )",       
                           
                           
	R"(       _                
	          \`\              
	     ,    |  \     _,.-^`) 
	    /|    /   `-'´  _.-;´  
	    | \--´  ´"` _.-´ .´    
	     \ `.____.-´   .´      
	      \           /        
	    .´ `-.__.´   /         
	   /           .´          
	  /           /            
	 .           .             
	 |           |             
	 |           '             
	 |            \            
	 '             \           
	  \             .          
	   .            |          
	   |            |          
	   |            |          )", 
                          
                          
R"(	         ,-.              
	      ,   \ `.     ,.-^`) 
	     /|   |   '-'´  _.:'  
	     | \-´  ´"` _.-´.'    
	     '  '.,__.-´   /      
	      \           /       
	    .´ `.,__.´   /        
	   /           .´         
	  /           /           
	 .           .            
	 |           |            
	 |           '            
	 |            \           
	 '             \          
	  \             .         
	   .            |         
	   |            |         
	   |            |                )",  

R"(           ____             
	       ,´`\   `'--._      
	      /   @)        `'-.  
	     /    .@            ) 
	    :    @|           .'  
	    '     \@        .'    
	     '     `       /      
	      \           /       
	    .´ `.,__.    /        
	   /           /          
	  .           .           
	  |           |           
	  |           |           
	  |           |           
	  |           '           
	  |            \          
	  '             .         
	   ¡            |         
	   |            |         
	   |            |         
	   |            |     )",    
R"(	         __        
	         ;\`\      
	        /  ) \     
	       /  .   `.   
	      .   |     \  
	      |   |      . 
	      |   \\     | 
	      \    `     ' 
	    .´ `.__     /  
	   /           /   
	  .           .    
	  |           |    
	  |           |    
	  |           |    
	  |           '    
	  |            \   
	  '             .  
	   ¡            |  
	   |            |  
  )",
                   
R"(	         __        
	         ;\`\      
	        /  ) \     
	       /  .   `.   
	      .   |     \  
	      |   |      . 
	      |   \\     | 
	      \    `     ' 
	    .´ `.__     /  
	   /           /   
	  /           /    
	 .           .     
	 |           |     
	 |           '     
	 |            \    
	 '             \   
	  \             .  
	   .            |  
	   |            |    )",
                   
	R"(    __          
	       ;\`.        
	       | \ `-.     
	       /  \   `.   
	      .   |     \  
	      |   |      | 
	      |   \\     | 
	      \    `     ' 
	    .´ `.__     /  
	   /           /   
	  /           /    
	 .           .     
	 |           |     
	 |           '     
	 |            \    
	 '             \   
	  \             .  
	   .            |  
	   |            |    )",
                    
    
R"(	    ¡\¯`.           
	    | :  `-._       
	    '  :     `-.    
	     |  :       '.  
	     |  ':.       ¡ 
	     '    `'      | 
	      \           ' 
	     / `-.__     /  
	    /           /   
	   /           /    
	  .           .     
	  |           |     
	 .            |     
	 '            \     
	  |            \    
	  '             .   
	   |            |   
	   |            |   
	   |            |    )",
                    
                    
                    
R"(	  ,´¯`'-.___        
	  \¯`.       `'-.   
	   \  \.         \  
	    \  ';.        | 
	     \   `'-      | 
	      \           ' 
	     .´`-.__     /  
	    /           /   
	   /           /    
	  .           .     
	  |           |     
	  |           |     
	  |           '     
	  |            \    
	  '             .   
	   |            |   
	   |            |   
	   |            | 
       |            |     )",
                     
                     
                     
                     
R"(	      _.--'''-._     
	 ,.--´          `.   
	/_..              \  
	`.  `:.,__         . 
	  `.   `''´        | 
	    `-.      .     | 
	       `'--'´      | 
	       '           ' 
	      /           /  
	     /           /   
	    /           .    
	   .            |    
	   |            |    
	   |            |    
	   |            |    
	   |            |    
	   |            |    )",
                       
                       
                       
                       
R"(	          __..__       
	       .-´      `-.    
	     .´            \   
	  _.´               \  
	.´    __..,          . 
	!,--''´¯¯     /      | 
	 ¯`'--.____.-´       ' 
	        ,           /  
	       /           /   
	      /           /    
	     /           /     
	    /           .      
	   .            |      
	   |            |      
	   |            |      
	   |            |      
	   |            |
       |            |   )",   
                        
                        
                        
                        
R"(	          _____         
	       .-´     `'-.     
	     .´            \    
	    /               \   
	  .´                 \  
	.´   _..;'    |       | 
	!,-''´¯¯    .´        ' 
	 ¯¯`'----'´          /  
	        /           /   
	       /           /    
	      /           /     
	     /           /      
	    /           /       
	   ¡            |       
	   |            |       
	   |            |       
	   |            |        )",
                         
                         
                         
                         
R"(	            ___          
	        .-'´   `'-.      
	      ,´           `.    
	     /               \   
	    .     ,           \  
	   ,'    //    |       . 
	  /   _,:´    ;        | 
	 ¡,.-'´  _,.-´         | 
	 `'----'´,            /  
	        /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |   
       |            |      )",    
                         
                         
                         
                         
R"(	           ____          
	        .-´    `'-.      
	      ,´           `.    
	     /               \   
	    .     ,           \  
	    ;    //    |       . 
	   /   ,:´    ,'       | 
	  .  _:´   _.´         | 
	  |;´__.--´           /  
	   ¯¯   /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |     
       |            |         )",

                         
                         
R"(	           ____          
	       .-´     `'-.      
	      /            `.    
	     /               \   
	    .     ,           \  
	    ;    //    |       . 
	   /   ,:´    ,'       | 
	  .  _:´   _.´         | 
	  |;´__.--´           /  
	   ¯¯   /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |     
       |            |       
       |            |        )",

                         
                         
R"(            ____          
	       .--´    `'-.      
	     .´            `.    
	     |               \   
	    /     ,           \  
	    ;    //    |       . 
	   /   ,:´    ,'       | 
	  .  _:´   _.´         | 
	  |;´__.--´           /  
	   ¯¯   /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |      )",  

                         
                         
R"(	           ____          
	        .-´    `'-.      
	      ,´           `.    
	    .´               \   
	    |     ,           \  
	    ;    //    |       . 
	   /   ,:´    ,'       | 
	  .  _:´   _.´         | 
	  |;´__.--´           /  
	   ¯¯   /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |   
       |            |        )",

                         
                         
R"(            ____          
	        .-´    `'-.      
	      ,´           `.    
	     /               \   
	   .´     ,           \  
	   ;    ,´/    |       . 
	  /    ,:´    ,'       | 
	  .  _:´   _.´         | 
	  |;´__.--´           /  
	   ¯¯   /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |        )",

                         
                         
R"(	           ____          
	        .-´    `'-.      
	      ,´           `.    
	     /               \   
	    /     ,           \  
	  .´    ,´)    |       . 
	  ;   ,´.´    ,'       | 
	  |  _:´   _.´         | 
	  |;´__.--´           /  
	   ¯¯   /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |     
       |            |      )",   

                         
                         
R"(	           ____          
	        .-´    `'-.      
	      ,´           `.    
	     /               \   
	    /     ,           \  
	   /    ,´)    |       . 
	  .   .´.´    ,'       | 
	 ;  ,´.´   _.´         | 
	 \|,´´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |    )",     

                         
                         
R"(	           ____          
	       .-'´    `'-.      
	     .´            `.    
	    /                \   
	   .     ,.           \  
	   ;    ;  )   |       . 
	  /   .´.-´   ,'       | 
	 ;  ,´.´   _.´         | 
	 \|,´´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |    
       |            |        )",

                         
                         
R"(	           ____          
	       .-'´    `'-.      
	     .´            `.    
	    /                \   
	   /    ,-.           \  
	  /   .´_  )   |       . 
	 | ,-/   ;´   ,'       | 
	 \`  \_.´  _.´         | 
	  |;´´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |   
       |            |         )",

                         
                         
R"(	          ___._          
	      .-'´     `'-.      
	    .´             `.    
	   /                 \   
	  /  .-'¯'.           \  
	 / ,`/ __  )   |       . 
	 \` /.´  )´   ,'       | 
	  ! \ _.´  _.´         | 
	  |;-´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |  
       |            |         )",

                         
                         
	R"(       __.._          
	       .'´     `'-.      
	    _.´            `.    
	  .´                 \   
	 /  ,.-'¯'.           \  
	/ ,/,  __  )   |       . 
	\| | .´  )´   ,'       | 
	 `.\/ _.´  _.´         | 
	  |;-´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |    
       |            |        )",

                         
                         
R"(	          _.-._          
	       .'´     `'-.      
	    .'´            `.    
	  .´  ___            \   
	,´ ,'´   `\           \  
	\V` ,  __  )   |       . 
	\ |/ .´  )´   ,'       | 
	 \`\/ _.´  _.´         | 
	  |;-´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |   
       |            |        )",

                         
                         
R"(	         _..--._         
	      .-´       `-.      
	   _.´             `.    
	,-´ ,.----.          \   
	`Vv` ,    `\          \  
	\|  /  __  /   |       . 
	 | / .´  )´   ,'       | 
	 |\ / _.´  _.´         | 
	 '|;-´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |     
       |            |         )",

                         
                         
R"(	        __.--.__         
	    _.-´        `'.      
	_.-´,___           `.    
	`Vv¯  / `-.          \   
	\|   /    `\          \  
	 :  /  __  /   |       . 
	 | / .´  )´   ,'       | 
	 |. / _.´  _.´         | 
	 '|;-´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |      
       |            |          )",
                         
                         
R"(	        __.--._          
	___.---´       `'-._     
	`Vv-,___            \    
	|/    / `-.          \   
	')   /    `\          \  
	·   /  __  /   |       . 
	 . / .´  )´   ,'       | 
	 (: / _.´  _.´         | 
	  |;-´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |   
       |            |        )",

                         
                         
R"(	 ____..-----.._          
	 `Vv-,_        `'-._     
	 |/    )`-.         `.   
	 `'   /   ´\         |   
	     /    `|          \  
	·   /  __  /   |       . 
	   / .´  )´   ,'       | 
	  . / _.´  _.´         | 
	 (|;-´_.--´           /  
	   ¯¯¯  /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |    
       |            |        )",

                         
R"(	  ________               
	  `Vv-,_   `'-._         
	  !)    )`.     `-._     
	       /   \        `.   
	      /   ´x\         |  
	     /    ` |         '. 
	.  ,´ ___  /   |       | 
	  / .´   |/   ,'       | 
	  |/   _.´ _.´         | 
	  ' ,-´_.-´           /  
	    ¯¯¯ /            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |        )",

R"(	    _____                
	    `Vv-,`-.             
	    ') \ ´, `-.          
	        )  \   `'-._     
	       /   _\       `.   
	      /   ´x|         \  
	    ,´    ` |          | 
	   /  _.._ /   |       | 
	  / .´   `/   ,'       | 
	  \ |    /  .´         | 
	    `,-'´_.´          /  
	     ¯¯¯¯            /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |            )",

R"(	    _____                
	    `Vv-,`-.             
	     ')\ ´, `-.          
	        )  \   `'-._     
	       /   _\       `.   
	      /   ´x|         \  
	    ,´    ` |          \ 
	   / _.-._  /  .       | 
	  / /    `)/   !       | 
	  `.\    ,´   /        | 
	     .--´ _.-´        /  
	      `¯¯¯           /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |        )",

R"(	    _____                
	    `Vv-,`-.             
	     `´\ ´, `-.          
	        \  `.  `'-._     
	        /  _ \      `.   
	       /  ´x) \       \  
	     ,´   `   |        \ 
	   .´ .--.._  /        | 
	   | (    \ ;´  |      | 
	   `--`   .´   .'      | 
	      \--´ _.-´       /  
	       ¯¯¯´          /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |        )",

R"(	    _____                
	    `Vv-,`-.             
	     ' \ ´, `-.          
	        \  `.  `'-._     
	        /  _ \      `.   
	       /  ´x) \       \  
	     .´   `   |        \ 
	   ,´,.---._  |        | 
	  / (_    \ `.'  |     | 
	  `--´ ,  '_.´  ,'     | 
	       \--´ _.-´      /  
	        ¯¯¯¯         /   
	      ,´            /    
	     /            ,´     
	    /            /       
	   .            /        
	   |            |        
	   |            |        
	   |            |        )",

    };
};


std::vector<std::string> Animation::shop() {
    return {
        "      ______________________",
        "      |\\\\\\\\\\||||||||////|",
        "      |   ___    SHOP    ___ |",
        "      |  |___|          |___||",
        "      |  |_|_|   __     |_|_||",
        "     _|_______________ ______|_",
        "    |                   |      |",
        "    |   [ ]       [ ]   | [ ]  |",
        "    |                   |      |",
        "    |___|_________|_____|______|"
    };
}

void Animation ::animate(const std::vector<std::string>& frames, int delayMs , int repeat ) {
    for (int i = 0; i < repeat; i++) {
        for (const auto& frame : frames) {
            clearScreen();
            std::cout << frame << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}


void Animation:: animateWalkingToShop(const std::vector<std::string>& shop, int animationSpeed , int totalFrames) {
    const int stickmanLine = shop.size() - 2;
    const int shopIndent = 25; 
    const int stopDistance = 3; 
    for (int frame = 0; frame <= totalFrames; ++frame) {
        clearScreen();
		int currentPos;
		if(shopIndent-stopDistance < frame){
			currentPos = shopIndent-stopDistance;
		}
		else{
			currentPos = frame;
		}

        for (size_t i = 0; i < shop.size(); ++i) {
            std::string line;
            if (i == stickmanLine - 1)
				line = std::string(currentPos, ' ') + " o ";
			else if (i == stickmanLine)
				line = std::string(currentPos, ' ') + "/|\\";
			else if (i == stickmanLine + 1)
				line = std::string(currentPos, ' ') + "/ \\";
			else
				line = std::string(currentPos, ' ');  

            while (line.length() < shopIndent)
                line += ' ';  

            line += shop[i];

            std::cout << line << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
    }

    std::cout << "\n>> Selamat datang di SHOP! <<\n";
}

