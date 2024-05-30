#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>

using namespace std;

#define GREEN_TEXT "\033[1;32m" // ANSI escape sequence for green color
#define DEFAULT_TEXT "\033[0m"  // ANSI escape sequence for default color

class Character {
public:
    string name;
    string gender;
    unordered_map<string, int> skills;
    unordered_map<string, int> personalityTraits;
    unordered_map<string, int> relationships;

    Character(string n, string g) : name(n), gender(g) {}

    void updateTrait(string trait, int value) {
        personalityTraits[trait] += value;
    }

    void updateSkill(string skill, int value) {
        skills[skill] += value;
    }

    void updateRelationship(string otherCharacter, int value) {
        relationships[otherCharacter] += value;
    }

    void display() {
        cout << "Character: " << name << " (Gender: " << gender << ")\n";
        cout << "Skills:\n";
        for (auto& skill : skills) {
            cout << "  " << skill.first << ": " << skill.second << endl;
        }
        cout << "Personality Traits:\n";
        for (auto& trait : personalityTraits) {
            cout << "  " << trait.first << ": " << trait.second << endl;
        }
        cout << "Relationships:\n";
        for (auto& relation : relationships) {
            cout << "  " << relation.first << ": " << relation.second << endl;
        }
    }
};

class Story {
public:
    string currentScene;
    unordered_map<string, vector<string>> choices; //using link list for choices
    unordered_map<string, string> outcomes; // Using a binary tree-like structure for outcomes
    unordered_map<string, bool> visitedChoices;

    Story()
    {
        // Initialize story choices and outcomes...
        initializeStory();
    }
    void initializeStory()
    {
        currentScene = "Start";
        choices["Start"] = { "Wake up in your apartment", "Walk through the Cyber City streets", "Check your messages" };
        outcomes["Wake up in your apartment"] = "You wake up in your high-tech apartment, ready to face the day.";
        outcomes["Walk through the Cyber City streets"] = "You step out into the bustling streets of Cyber City, neon lights everywhere.";
        outcomes["Check your messages"] = "You check your messages and find an urgent request from a friend.";

        choices["Wake up in your apartment"] = { "Meet a Mysterious Stranger", "Go to Work", "Visit a Friend" };
        outcomes["Meet a Mysterious Stranger"] = "You encounter a mysterious stranger who offers you a dangerous job.";
        outcomes["Go to Work"] = "You go to your job as a tech engineer, but something feels off.";
        outcomes["Visit a Friend"] = "You visit an old friend who needs your help with a personal matter.";

        choices["Walk through the Cyber City streets"] = { "Fight with a Gang", "Visit a Nightclub", "Head to the Market" };
        outcomes["Fight with a Gang"] = "You get into a fight with a local gang. It's tough, but you manage to escape.";
        outcomes["Visit a Nightclub"] = "You visit a popular nightclub and meet some interesting characters.";
        outcomes["Head to the Market"] = "You head to the market and discover a rare tech artifact.";

        choices["Check your messages"] = { "Respond to Friend", "Ignore the Messages", "Delete All Messages" };
        outcomes["Respond to Friend"] = "You respond to your friend and agree to meet up.";
        outcomes["Ignore the Messages"] = "You ignore the messages and continue with your day.";
        outcomes["Delete All Messages"] = "You delete all messages and clear your inbox.";

        choices["Meet a Mysterious Stranger"] = { "Accept the Job", "Decline the Job", "Investigate Stranger" };
        outcomes["Accept the Job"] = "You accept the job and embark on a risky mission.";
        outcomes["Decline the Job"] = "You decline the job, but the stranger warns you that you may regret it.";
        outcomes["Investigate Stranger"] = "You decide to investigate the stranger's background.";

        choices["Go to Work"] = { "Talk to Boss", "Sneak into Restricted Area", "Work on Project", "Explore a Hidden Facility" };
        outcomes["Talk to Boss"] = "You have a tense conversation with your boss.";
        outcomes["Sneak into Restricted Area"] = "You sneak into a restricted area and discover a dark secret.";
        outcomes["Work on Project"] = "You work on your project, making significant progress.";
        outcomes["Explore a Hidden Facility"] = "You stumble upon an opportunity to explore a hidden facility nearby.";

        choices["Visit a Friend"] = { "Help Friend", "Chat with Friend", "Leave Early" };
        outcomes["Help Friend"] = "You help your friend solve their problem.";
        outcomes["Chat with Friend"] = "You chat with your friend and catch up on old times.";
        outcomes["Leave Early"] = "You leave early, feeling something is off.";

        choices["Fight with a Gang"] = { "Escape", "Fight Back", "Call for Help" };
        outcomes["Escape"] = "You manage to escape the gang, but they are still looking for you.";
        outcomes["Fight Back"] = "You fight back and manage to defeat the gang members.";
        outcomes["Call for Help"] = "You call for help and the authorities arrive just in time.";

        choices["Visit a Nightclub"] = { "Dance", "Talk to Bartender", "Observe People" };
        outcomes["Dance"] = "You hit the dance floor and enjoy the music.";
        outcomes["Talk to Bartender"] = "You talk to the bartender and learn some interesting information.";
        outcomes["Observe People"] = "You observe the people around you and notice some suspicious activity.";

        choices["Head to the Market"] = { "Buy Artifact", "Leave Market", "Investigate Seller" };
        outcomes["Buy Artifact"] = "You buy the artifact and feel a strange energy from it.";
        outcomes["Leave Market"] = "You leave the market and head home.";
        outcomes["Investigate Seller"] = "You investigate the seller and uncover a hidden conspiracy.";

        choices["Respond to Friend"] = { "Meet Friend", "Postpone Meeting", "Ask for Details" };
        outcomes["Meet Friend"] = "You meet your friend and they tell you about a dangerous situation.";
        outcomes["Postpone Meeting"] = "You postpone the meeting but your friend insists it's urgent.";
        outcomes["Ask for Details"] = "You ask for more details and your friend reveals a shocking secret.";

        // Additional layers for "Accept the Job" outcome
        choices["Accept the Job"] = { "Gather Equipment", "Research Mission", "Inform Allies" };
        outcomes["Gather Equipment"] = "You gather necessary equipment for the mission ahead.";
        outcomes["Research Mission"] = "You spend time researching the mission to gather intel.";
        outcomes["Inform Allies"] = "You inform your trusted allies about the mission and seek their advice.";

        // Additional layers for "Sneak into Restricted Area" outcome
        choices["Sneak into Restricted Area"] = { "Gather Evidence", "Confront Authorities", "Stay Silent" };
        outcomes["Gather Evidence"] = "You gather evidence of wrongdoing in the restricted area.";
        outcomes["Confront Authorities"] = "You confront the authorities about what you discovered.";
        outcomes["Stay Silent"] = "You choose to stay silent, fearing the consequences of speaking out.";

        // Additional layers for "Help Friend" outcome
        choices["Help Friend"] = { "Offer Practical Solution", "Provide Emotional Support", "Seek Professional Help" };
        outcomes["Offer Practical Solution"] = "You offer a practical solution to your friend's problem.";
        outcomes["Provide Emotional Support"] = "You provide emotional support, listening to your friend's concerns.";
        outcomes["Seek Professional Help"] = "You suggest seeking professional help to deal with the issue.";

        // Additional layers for "Talk to Bartender" outcome
        choices["Talk to Bartender"] = { "Follow Bartender's Tip", "Ignore Bartender's Tip", "Investigate Further" };
        outcomes["Follow Bartender's Tip"] = "You follow the bartender's tip and uncover a hidden secret.";
        outcomes["Ignore Bartender's Tip"] = "You ignore the bartender's tip and continue your night.";
        outcomes["Investigate Further"] = "You decide to investigate further based on the bartender's hint.";

        // Additional layers for "Buy Artifact" outcome
        choices["Buy Artifact"] = { "Study Artifact", "Sell Artifact", "Guard Artifact" };
        outcomes["Study Artifact"] = "You study the artifact, unlocking its mysteries.";
        outcomes["Sell Artifact"] = "You sell the artifact for a significant profit.";
        outcomes["Guard Artifact"] = "You decide to keep the artifact safe, realizing its potential danger.";

        // Additional layers for "Meet Friend" outcome
        choices["Meet Friend"] = { "Offer Assistance", "Plan Course of Action", "Keep Distance" };
        outcomes["Offer Assistance"] = "You offer immediate assistance to your friend in need.";
        outcomes["Plan Course of Action"] = "You and your friend plan a course of action to tackle the situation.";
        outcomes["Keep Distance"] = "You choose to keep a safe distance from your friend's problem.";

        // Additional layers for "Investigate Seller" outcome
        choices["Investigate Seller"] = { "Confront Seller", "Report to Authorities", "Ignore Seller" };
        outcomes["Confront Seller"] = "You confront the seller about the hidden conspiracy, demanding answers.";
        outcomes["Report to Authorities"] = "You report your findings to the authorities, hoping for an investigation.";
        outcomes["Ignore Seller"] = "You choose to ignore the seller's involvement, focusing on other matters.";

        // Additional layers for "Postpone Meeting" outcome
        choices["Postpone Meeting"] = { "Offer Alternatives", "Express Concern", "Insist on Postponement" };
        outcomes["Offer Alternatives"] = "You suggest alternative ways to handle the urgent situation.";
        outcomes["Express Concern"] = "You express your concern for your friend's safety and well-being.";
        outcomes["Insist on Postponement"] = "You insist on postponing the meeting, prioritizing your friend's urgency.";

        // Additional layers for "Ask for Details" outcome
        choices["Ask for Details"] = { "Offer Support", "Investigate Further", "Advise Caution" };
        outcomes["Offer Support"] = "You offer your support to your friend, assuring them of your help.";
        outcomes["Investigate Further"] = "You investigate further into the shocking secret, uncovering more details.";
        outcomes["Advise Caution"] = "You advise caution, warning your friend about the potential risks involved.";

        // Additional layers for "Decline the Job" outcome
        choices["Decline the Job"] = { "Seek Alternatives", "Stay Alert", "Investigate Stranger" };
        outcomes["Seek Alternatives"] = "You look for alternative job opportunities.";
        outcomes["Stay Alert"] = "You stay alert, wary of any future encounters with the stranger.";
        outcomes["Investigate Stranger"] = "You decide to investigate the stranger further to understand their motives.";

        // Additional layers for "Fight Back" outcome
        choices["Fight Back"] = { "Escape", "Call for Reinforcements", "Negotiate Truce" };
        outcomes["Escape"] = "You manage to escape the fight, regrouping to plan your next move.";
        outcomes["Call for Reinforcements"] = "You call for reinforcements to aid you in the fight.";
        outcomes["Negotiate Truce"] = "You negotiate a truce with the gang, seeking a peaceful resolution.";

        // Additional layers for "Talk to Boss" outcome
        choices["Talk to Boss"] = { "Express Concerns", "Investigate Office", "Seek Promotion" };
        outcomes["Express Concerns"] = "You express your concerns to your boss, seeking clarification.";
        outcomes["Investigate Office"] = "You investigate your office further, looking for clues about the unsettling feeling.";
        outcomes["Seek Promotion"] = "You focus on your work, aiming for a promotion to gain more influence.";

        // Additional layers for "Chat with Friend" outcome
        choices["Chat with Friend"] = { "Offer Advice", "Share Similar Experience", "Discuss Solutions" };
        outcomes["Offer Advice"] = "You offer advice based on your own experiences to help your friend.";
        outcomes["Share Similar Experience"] = "You share a similar experience to let your friend know they're not alone.";
        outcomes["Discuss Solutions"] = "You discuss potential solutions together to address your friend's issue.";

        // Additional layers for "Leave Market" outcome
        choices["Leave Market"] = { "Return Home", "Investigate Artifact", "Inform Authorities" };
        outcomes["Return Home"] = "You decide to return home, leaving the market behind.";
        outcomes["Investigate Artifact"] = "You investigate the artifact further to understand its significance.";
        outcomes["Inform Authorities"] = "You inform the authorities about the artifact, seeking their guidance.";

        // Additional layers for "Ignore the Messages" outcome
        choices["Ignore the Messages"] = { "Reflect on Decision", "Resume Daily Routine", "Regret Ignoring" };
        outcomes["Reflect on Decision"] = "You reflect on your decision to ignore the messages, considering its implications.";
        outcomes["Resume Daily Routine"] = "You continue with your daily routine, pushing the messages out of your mind.";
        outcomes["Regret Ignoring"] = "You start to regret ignoring the messages, wondering if it was a mistake.";

        // Additional layers for "Dance" outcome
        choices["Dance"] = { "Enjoy the Night", "Meet New People", "Spot Suspicious Activity" };
        outcomes["Enjoy the Night"] = "You lose yourself in the music, enjoying every moment.";
        outcomes["Meet New People"] = "You mingle with other club-goers, making new connections.";
        outcomes["Spot Suspicious Activity"] = "You notice suspicious behavior and decide to investigate further.";

        // Additional layers for "Reflect on Decision" outcome
        choices["Reflect on Decision"] = { "Reach Out to Sender", "Research Situation", "Trust Initial Instincts" };
        outcomes["Reach Out to Sender"] = "You reach out to the sender to gather more information.";
        outcomes["Research Situation"] = "You research the situation to better understand the context of the messages.";
        outcomes["Trust Initial Instincts"] = "You trust your initial instincts and stand by your decision to ignore the messages.";

        // Additional layers for "Resume Daily Routine" outcome
        choices["Resume Daily Routine"] = { "Focus on Work", "Engage in Hobbies", "Connect with Friends" };
        outcomes["Focus on Work"] = "You immerse yourself in your work to distract from the messages.";
        outcomes["Engage in Hobbies"] = "You indulge in your hobbies to relax and unwind.";
        outcomes["Connect with Friends"] = "You spend time with friends, seeking comfort and support.";

        // Additional layers for "Regret Ignoring" outcome
        choices["Regret Ignoring"] = { "Attempt to Retrieve Messages", "Stay Vigilant", "Prepare for Consequences" };
        outcomes["Attempt to Retrieve Messages"] = "You try to retrieve the deleted messages, hoping for more clarity.";
        outcomes["Stay Vigilant"] = "You remain vigilant, keeping an eye out for any further communication.";
        outcomes["Prepare for Consequences"] = "You prepare yourself for potential consequences of ignoring the messages, bracing for impact.";

        // Additional layers for "Investigate Further" outcome
        choices["Investigate Further"] = { "Gather Clues", "Seek Expert Advice", "Involve Authorities" };
        outcomes["Gather Clues"] = "You gather more clues to piece together the puzzle.";
        outcomes["Seek Expert Advice"] = "You seek advice from experts to gain insight into the situation.";
        outcomes["Involve Authorities"] = "You involve the authorities, escalating the investigation to a higher level.";

        // Additional layers for "Advise Caution" outcome
        choices["Advise Caution"] = { "Offer Protection", "Research Threat", "Create Escape Plan" };
        outcomes["Offer Protection"] = "You offer protection to your friend, ensuring their safety.";
        outcomes["Research Threat"] = "You research the potential threat, gathering information to better prepare.";
        outcomes["Create Escape Plan"] = "You create an escape plan in case the situation escalates.";

        // Additional layers for "Inform Allies" outcome
        choices["Inform Allies"] = { "Formulate Strategy", "Request Assistance", "Keep Eyes Open" };
        outcomes["Formulate Strategy"] = "You and your allies formulate a strategy to tackle the mission.";
        outcomes["Request Assistance"] = "You request assistance from your allies to strengthen your position.";
        outcomes["Keep Eyes Open"] = "You keep your eyes open for any additional information or developments.";

        // Additional layers for "Confront Authorities" outcome
        choices["Confront Authorities"] = { "Present Evidence", "Seek Explanation", "Request Protection" };
        outcomes["Present Evidence"] = "You present your evidence to the authorities, demanding action.";
        outcomes["Seek Explanation"] = "You seek an explanation from the authorities regarding the situation.";
        outcomes["Request Protection"] = "You request protection from the authorities due to the risks involved.";

        // Additional layers for "Stay Silent" outcome
        choices["Stay Silent"] = { "Monitor Situation", "Seek Legal Advice", "Prepare for Repercussions" };
        outcomes["Monitor Situation"] = "You monitor the situation closely, waiting for the right moment to act.";
        outcomes["Seek Legal Advice"] = "You seek legal advice to understand your rights and options.";
        outcomes["Prepare for Repercussions"] = "You prepare yourself for potential repercussions, bracing for any fallout.";

        // Additional layers for "Offer Alternatives" outcome
        choices["Offer Alternatives"] = { "Suggest Alternative Plan", "Provide Support", "Stay Available" };
        outcomes["Suggest Alternative Plan"] = "You suggest an alternative plan to address the urgent situation.";
        outcomes["Provide Support"] = "You offer your support to your friend, standing by them through the ordeal.";
        outcomes["Stay Available"] = "You assure your friend that you're available to help whenever they need.";

        // Additional layers for "Express Concern" outcome
        choices["Express Concern"] = { "Offer Assistance", "Listen Actively", "Seek Professional Help" };
        outcomes["Offer Assistance"] = "You offer your immediate assistance to address your friend's concerns.";
        outcomes["Listen Actively"] = "You actively listen to your friend, validating their feelings and concerns.";
        outcomes["Seek Professional Help"] = "You suggest seeking professional help to deal with the issue effectively.";

        // Additional layers for "Insist on Postponement" outcome
        choices["Insist on Postponement"] = { "Arrange Emergency Meeting", "Provide Reassurance", "Stay in Contact" };
        outcomes["Arrange Emergency Meeting"] = "You arrange an emergency meeting to address the urgent situation.";
        outcomes["Provide Reassurance"] = "You provide reassurance to your friend, ensuring them that their concerns are valid.";
        outcomes["Stay in Contact"] = "You promise to stay in constant contact with your friend, offering support from afar.";

        // Additional layers for "Explore a Hidden Facility" outcome
        choices["Explore a Hidden Facility"] = { "Investigate Laboratories", "Hack Security Systems", "Avoid Detection" };
        outcomes["Investigate Laboratories"] = "You explore the laboratories within the hidden facility, uncovering groundbreaking experiments.";
        outcomes["Hack Security Systems"] = "You hack into the security systems, gaining access to restricted areas and valuable information.";
        outcomes["Avoid Detection"] = "You carefully navigate the facility, avoiding detection and gathering intel without raising suspicion.";

        // Additional layers for "Investigate Laboratories" outcome
        choices["Investigate Laboratories"] = { "Retrieve Research Data", "Rescue Captive", "Activate Experimental Device" };
        outcomes["Retrieve Research Data"] = "You retrieve valuable research data, uncovering technological advancements that could change the world.";
        outcomes["Rescue Captive"] = "You discover a captive held within the facility and rescue them, earning their gratitude and assistance.";
        outcomes["Activate Experimental Device"] = "You activate an experimental device, triggering unforeseen consequences that alter the facility's environment.";

        // Additional layers for "Hack Security Systems" outcome
        choices["Hack Security Systems"] = { "Download Classified Files", "Sabotage Operations", "Plant False Data" };
        outcomes["Download Classified Files"] = "You successfully download classified files containing valuable information about the facility's operations.";
        outcomes["Sabotage Operations"] = "You sabotage the facility's operations, disrupting their plans and creating chaos within their ranks.";
        outcomes["Plant False Data"] = "You plant false data within the facility's systems, misleading their efforts and buying time for further investigation.";

        // Additional layers for "Avoid Detection" outcome
        choices["Avoid Detection"] = { "Stealthily Gather Intel", "Eavesdrop on Conversations", "Disguise Yourself" };
        outcomes["Stealthily Gather Intel"] = "You stealthily gather intel on the facility's activities, remaining undetected by security.";
        outcomes["Eavesdrop on Conversations"] = "You eavesdrop on conversations between facility personnel, uncovering valuable information.";
        outcomes["Disguise Yourself"] = "You disguise yourself as a facility employee, blending in seamlessly and gaining access to restricted areas.";

        // Endings for "Explore a Hidden Facility" outcome
        outcomes["Explore a Hidden Facility"] += " Your exploration of the hidden facility reveals shocking truths about its purpose and the forces behind it.";
        outcomes["Investigate Laboratories"] += " Your investigation into the laboratories uncovers groundbreaking research that could shape the future.";
        outcomes["Hack Security Systems"] += " Hacking the security systems provides valuable intelligence, exposing the facility's secrets to the world.";
        outcomes["Avoid Detection"] += " Your stealthy approach allows you to gather intel without alerting the facility's authorities, maintaining the element of surprise.";

        // Endings for "Accept the Job" outcome
        outcomes["Accept the Job"] += " The mission was successful, and you receive a handsome reward for your efforts.";
        outcomes["Gather Equipment"] += " Your preparation pays off, ensuring your safety during the mission.";
        outcomes["Research Mission"] += " Your research provides valuable insights, helping you navigate through challenges.";
        outcomes["Inform Allies"] += " Your allies prove to be invaluable, offering crucial support throughout the mission.";

        // Endings for "Sneak into Restricted Area" outcome
        outcomes["Sneak into Restricted Area"] += " Your stealthy approach uncovers vital information hidden within the restricted area.";
        outcomes["Gather Evidence"] += " The evidence you collect leads to the exposure of corruption, bringing justice to light.";
        outcomes["Confront Authorities"] += " Your bravery in confronting the authorities leads to positive changes in the system.";
        outcomes["Stay Silent"] += " Your decision to stay silent prevents further complications, but the truth remains buried.";

        // Endings for "Help Friend" outcome
        outcomes["Help Friend"] += " Your assistance strengthens your bond, and your friend is forever grateful for your support.";
        outcomes["Offer Practical Solution"] += " Your practical solution resolves the issue, bringing peace of mind to your friend.";
        outcomes["Provide Emotional Support"] += " Your emotional support helps your friend overcome their challenges, strengthening your friendship.";
        outcomes["Seek Professional Help"] += " Seeking professional help proves effective, and your friend finds the guidance they needed.";

        // Endings for "Talk to Bartender" outcome
        outcomes["Talk to Bartender"] += " The bartender's tip leads you to a new adventure, uncovering secrets beyond imagination.";
        outcomes["Follow Bartender's Tip"] += " Following the bartender's tip leads to unexpected rewards, changing your fate.";
        outcomes["Ignore Bartender's Tip"] += " Ignoring the tip keeps you safe, but you wonder about the mysteries left unexplored.";
        outcomes["Investigate Further"] += " Your investigation reveals hidden truths, altering the course of events.";

        // Endings for "Buy Artifact" outcome
        outcomes["Buy Artifact"] += " The artifact becomes a valuable asset, shaping the future in unexpected ways.";
        outcomes["Study Artifact"] += " Your study of the artifact unlocks its true potential, revealing secrets of ancient knowledge.";
        outcomes["Sell Artifact"] += " Selling the artifact brings temporary wealth, but its true value remains undiscovered.";
        outcomes["Guard Artifact"] += " Guarding the artifact protects you from danger, but its power may yet be unleashed.";

        // Endings for "Meet Friend" outcome
        outcomes["Meet Friend"] += " Your meeting with your friend strengthens your bond, and together you face the challenges ahead.";
        outcomes["Offer Assistance"] += " Your immediate assistance resolves the crisis, earning you a lifelong ally.";
        outcomes["Plan Course of Action"] += " Planning together leads to victory, proving the strength of your friendship.";
        outcomes["Keep Distance"] += " Keeping your distance protects you, but you wonder about the cost of isolation.";

        // Endings for "Investigate Seller" outcome
        outcomes["Investigate Seller"] += " Your investigation uncovers the truth, and justice is served.";
        outcomes["Confront Seller"] += " Confronting the seller exposes the conspiracy, earning you respect as a truth-seeker.";
        outcomes["Report to Authorities"] += " Reporting your findings leads to positive changes, restoring trust in the system.";
        outcomes["Ignore Seller"] += " Ignoring the seller's involvement protects you, but the conspiracy continues to thrive.";

        // Endings for "Postpone Meeting" outcome
        outcomes["Postpone Meeting"] += " Postponing the meeting proves to be the right choice, allowing you to address the urgent situation.";
        outcomes["Offer Alternatives"] += " Offering alternatives demonstrates your flexibility and commitment to your friend's needs.";
        outcomes["Express Concern"] += " Expressing concern strengthens your friendship, fostering a deeper connection.";
        outcomes["Insist on Postponement"] += " Insisting on postponement shows your dedication to your friend's well-being, building trust.";

        // Endings for "Ask for Details" outcome
        outcomes["Ask for Details"] += " Asking for details strengthens your bond, and together you face the challenges ahead.";
        outcomes["Offer Support"] += " Offering support strengthens your friendship, showing your loyalty and trustworthiness.";
        outcomes["Investigate Further"] += " Investigating further reveals hidden truths, altering the course of events.";
        outcomes["Advise Caution"] += " Advising caution protects your friend, showing your care and concern for their well-being.";

        // Endings for "Gather Evidence" outcome
        outcomes["Gather Evidence"] += " You gather evidence of wrongdoing in the restricted area.";
        // Mini-game challenge for "Gather Evidence"
        choices["Gather Evidence"] = { "Play Mini-Game", "Abort Mission" };

        // Add additional layers and depth to the choices and outcomes...
    }

    void makeChoice(int choiceIndex) 
    {
        if (choiceIndex >= 0 && choiceIndex < choices[currentScene].size()) 
        {
            string nextScene = choices[currentScene][choiceIndex];
            if (nextScene == "Play Mini-Game") 
            {
                // Call the mini-game function
                bool miniGameResult = miniGame();
                if (miniGameResult) 
                {
                    // Player successfully completes the mini-game, continue with the outcome
                    currentScene = "Gather Evidence";
                }
                else 
                {
                    // Player fails the mini-game, handle consequences
                    cout << "You were caught while trying to gather evidence and faced severe consequences." << endl;
                    currentScene = "Start"; // Go back to the start or any other appropriate scene
                }
            }
            else 
            {
                currentScene = nextScene;
            }
            visitedChoices[currentScene] = true; // Mark the choice as visited
            if (outcomes.find(currentScene) != outcomes.end()) 
            {
                cout << outcomes[currentScene] << endl;
                if (choices.find(currentScene) == choices.end()) 
                {
                    cout << "You reached an ending. Press 1 to go back to the start: ";
                    int goBackChoice;
                    cin >> goBackChoice;
                    if (goBackChoice == 1) 
                    {
                        currentScene = "Start"; // Go back to the start
                    }
                }
            }
        }
        else 
        {
            cout << "Invalid choice! Try again.\n";
        }
    }

    void displayScene()
    {
        system("cls");
        cout << "Current Scene: " << currentScene << endl;
        if (outcomes.find(currentScene) != outcomes.end()) 
        {
            cout << outcomes[currentScene] << endl;
        }
        cout << "Choices:" << endl;
        for (int i = 0; i < choices[currentScene].size(); ++i) 
        {
            cout << i + 1 << ": ";
            if (visitedChoices.find(choices[currentScene][i]) != visitedChoices.end() && visitedChoices[choices[currentScene][i]]) 
            {
                cout << GREEN_TEXT; // Change color to green for visited choices
            }
            cout << choices[currentScene][i] << DEFAULT_TEXT << endl; // Reset color to default
        }
    }

    bool miniGame() 
    {
        srand(time(0)); // Seed the random number generator with the current time
        int randomNumber = rand() % 10 + 1; // Generates a random number between 1 and 10

        int guess;
        cout << "Guess a number between 1 and 10: ";
        cin >> guess;

        if (guess == randomNumber) 
        {
            cout << "Congratulations! You win the mini-game!" << endl;
            return true; // Player successfully completes the mini-game
        }
        else 
        {
            cout << "Sorry, you lose the mini-game." << endl;
            return false; // Player fails the mini-game
        }
    }
};

void showIntroduction() 
{
    cout << "Welcome to Cyber Adventure 2077!\n";
    cout << R"(
        ____            _               _                 
       / ___|___  _ __ | |_ _   _ _ __ | |_ _   _ _ __ ___ 
      | |   / _ \| '_ \| __| | | | '_ \| __| | | | '__/ _ \
      | |__| (_) | | | | |_| |_| | | | | |_| |_| | | |  __/
       \____\___/|_| |_|\__|\__,_|_| |_|\__|\__,_|_|  \___|
                                                           
    )" << endl;
    cout << "Make choices to progress through the story and see how your decisions affect the characters and the narrative.\n";
}

Character createCharacter()
{
    string name;
    string gender;
    int points;

    cout << "Enter your character's name: ";
    getline(cin, name);

    cout << "Select your character's gender (Male/Female/Other): ";
    getline(cin, gender);

    Character newCharacter(name, gender);

    cout << "Allocate points to your skills (You have 10 points):\n";
    string skills[] = { "Hacking", "Combat", "Charisma" };
    points = 10;

    for (string skill : skills) 
    {
        int value;
        cout << skill << ": ";
        cin >> value;
        if (value <= points) 
        {
            newCharacter.updateSkill(skill, value);
            points -= value;
        }
        else {
            cout << "Not enough points. Try again.\n";
            skill = skill;
        }
    }

    cout << "Allocate points to your personality traits (You have 10 points):\n";
    string traits[] = { "Courage", "Intelligence", "Empathy" };
    points = 10;

    for (string trait : traits) 
    {
        int value;
        cout << trait << ": ";
        cin >> value;
        if (value <= points) 
        {
            newCharacter.updateTrait(trait, value);
            points -= value;
        }
        else 
        {
            cout << "Not enough points. Try again.\n";
            trait = trait;
        }
    }

    return newCharacter;
}

int main() 
{
    showIntroduction();

    Character hero = createCharacter();

    Story myStory;

    cin.ignore(); // Clear newline character from the input buffer

    while (true) {

        myStory.displayScene();

        int choice;
        cout << "Enter choice number: ";
        cin >> choice;

        if (choice < 1 || choice > myStory.choices[myStory.currentScene].size()) {
            cout << "Invalid choice! Please try again.\n";
        }
        else {
            myStory.makeChoice(choice - 1);
        }

        cout << "\nCharacter Status:\n";
        hero.display();
        cout << endl;
    }

    return 0;
}