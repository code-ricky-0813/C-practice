#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef enum esuit {
  SPADES = 832,
  HEARTS = 574,
  DIAMONDS = 456,
  CLUBS = 192
} Suit;

typedef enum eface {
  ACE = 3947,
  DEUCE = 4537,
  THREE = 6696,
  FOUR = 7729,
  FIVE = 8374,
  SIX = 9295,
  SEVEN = 11491,
  EIGHT = 13638,
  NINE = 14554,
  TEN = 15332,
  JACK = 18987,
  QUEEN = 20215,
  KING = 213643
} Face;

typedef struct card {
  Suit suit;
  Face face;
} Card;

typedef char Str[50];
typedef Card Hand[5];

bool InputHand(Hand hand) {
  int count = 0;
    char suit_str, face_str[10];

    while(scanf(" %c %s", &suit_str, face_str) == 2) {
        if (suit_str == '-' && strcmp(face_str, "1") == 0) break;

        switch (suit_str) {
            case 'S': hand[count].suit = SPADES; break;
            case 'H': hand[count].suit = HEARTS; break;
            case 'D': hand[count].suit = DIAMONDS; break;
            case 'C': hand[count].suit = CLUBS; break;
            default: return false;
        }

        if (strcmp(face_str, "A") == 0) hand[count].face = ACE;
        else if (strcmp(face_str, "2") == 0) hand[count].face = DEUCE;
        else if (strcmp(face_str, "3") == 0) hand[count].face = THREE;
        else if (strcmp(face_str, "4") == 0) hand[count].face = FOUR;
        else if (strcmp(face_str, "5") == 0) hand[count].face = FIVE;
        else if (strcmp(face_str, "6") == 0) hand[count].face = SIX;
        else if (strcmp(face_str, "7") == 0) hand[count].face = SEVEN;
        else if (strcmp(face_str, "8") == 0) hand[count].face = EIGHT;
        else if (strcmp(face_str, "9") == 0) hand[count].face = NINE;
        else if (strcmp(face_str, "10") == 0) hand[count].face = TEN;
        else if (strcmp(face_str, "J") == 0) hand[count].face = JACK;
        else if (strcmp(face_str, "Q") == 0) hand[count].face = QUEEN;
        else if (strcmp(face_str, "K") == 0) hand[count].face = KING;
        else return false;
        count++;
    }
    
    if (count != 5) return false;
    return true;
}

void PrintCard(Card card, char* output) {
    const char* suit_str;
    const char* face_str;

    switch (card.suit) {
        case SPADES: suit_str = "Spades"; break;
        case HEARTS: suit_str = "Hearts"; break;
        case DIAMONDS: suit_str = "Diamonds"; break;
        case CLUBS: suit_str = "Clubs"; break;
    }

    switch (card.face) {
        case ACE: face_str = "Ace"; break;
        case DEUCE: face_str = "Deuce"; break;
        case THREE: face_str = "Three"; break;
        case FOUR: face_str = "Four"; break;
        case FIVE: face_str = "Five"; break;
        case SIX: face_str = "Six"; break;
        case SEVEN: face_str = "Seven"; break;
        case EIGHT: face_str = "Eight"; break;
        case NINE: face_str = "Nine"; break;
        case TEN: face_str = "Ten"; break;
        case JACK: face_str = "Jack"; break;
        case QUEEN: face_str = "Queen"; break;
        case KING: face_str = "King"; break;
    }

    sprintf(output, "%s of %s", face_str, suit_str);
}

void PrintHand(Hand hand) {
    char output[100];
    for (int i = 0; i < 5; i++) {
        PrintCard(hand[i], output);
        printf("%s\n", output);
    }
}

int Order(Face face) {
    switch (face) {
        case ACE: return 13;
        case KING: return 12;
        case QUEEN: return 11;
        case JACK: return 10;
        case TEN: return 9;
        case NINE: return 8;
        case EIGHT: return 7;
        case SEVEN: return 6;
        case SIX: return 5;
        case FIVE: return 4;
        case FOUR: return 3;
        case THREE: return 2;
        case DEUCE: return 1;
        default: return 0;
    }
}

int OrderSuit(Suit suit) {
    switch (suit) {
        case SPADES: return 4;
        case HEARTS: return 3;
        case CLUBS: return 2;
        case DIAMONDS: return 1;
        default: return 0;
    }
}

bool BiggerThan(Card card1, Card card2) {
    int face1 = Order(card1.face);
    int face2 = Order(card2.face);
    
    if (face1 > face2) {
        return true;
    } else if (face1 < face2) {
        return false;
    }

    int suit1 = OrderSuit(card1.suit);
    int suit2 = OrderSuit(card2.suit);

    return suit1 > suit2;
}

Card FindLargest(Hand hand) {
    Card largest = hand[0];

    for (int i = 1; i < 5; i++) {
        if (BiggerThan(hand[i], largest)) {
            largest = hand[i];
        }
    }

    return largest;
}

bool IsFlush(Hand hand) {
    Suit suit = hand[0].suit;

    for (int i = 1; i < 5; i++) {
        if (hand[i].suit != suit) {
            return false;
        }
    }

    Card largest = FindLargest(hand);

    int max_index = 0;
    for (int i = 0; i < 5; i++) {
        if (hand[i].face == largest.face && hand[i].suit == largest.suit) {
            max_index = i;
            break;
        }
    }

    if (max_index != 0) {
        Card temp = hand[0];
        hand[0] = hand[max_index];
        hand[max_index] = temp;
    }

    return true;
}

bool IsStraight(Hand hand) {
    int face_values[5];
    for (int i = 0; i < 5; i++) {
        face_values[i] = Order(hand[i].face);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (face_values[j] > face_values[j + 1]) {
                int temp = face_values[j];
                face_values[j] = face_values[j + 1];
                face_values[j + 1] = temp;
            }
        }
    }

    bool is_straight = true;
    for (int i = 0; i < 4; i++) {
        if (face_values[i] + 1 != face_values[i + 1]) {
            is_straight = false;
            break;
        }
    }

    bool is_wheel = false;
    if (!is_straight && face_values[0] == 1 && face_values[1] == 2 && face_values[2] == 3 &&
        face_values[3] == 4 && face_values[4] == 13) {
        is_straight = true;
        is_wheel = true;
    }

    if (is_straight) {
        if (is_wheel) {
            int index_five = -1;
            for (int i = 0; i < 5; i++) {
                if (Order(hand[i].face) == 4) {
                    index_five = i;
                    break;
                }
            }
            if (index_five != 0) {
                Card temp = hand[0];
                hand[0] = hand[index_five];
                hand[index_five] = temp;
            }
        } else {
            Card largest = FindLargest(hand);
            int max_index = 0;
            for (int i = 0; i < 5; i++) {
                if (hand[i].face == largest.face && hand[i].suit == largest.suit) {
                    max_index = i;
                    break;
                }
            }
            if (max_index != 0) {
                Card temp = hand[0];
                hand[0] = hand[max_index];
                hand[max_index] = temp;
            }
        }
    }

    return is_straight;
}

bool IsStraightFlush(Hand hand) {
    return IsFlush(hand) && IsStraight(hand);
}

bool IsFourOfAKind(Hand hand) {
    int count[14] = {0};
    int four_value;

    for (int i = 0; i < 5; i++) {
        int order = Order(hand[i].face);
        count[order]++;
    }

    int is_four_of_a_kind = 0;

    for (int i = 1; i < 14; i++) {
        if (count[i] == 4) {
            is_four_of_a_kind = 1;
            four_value = i;
            break;
        }
    }

    if (is_four_of_a_kind) {
        int max_index = 0;

        for (int i = 0; i < 5; i++) {
            if (Order(hand[i].face) == four_value) {
                if (BiggerThan(hand[i], hand[max_index])) {
                    max_index = i;
                }
            }
        }

        if (max_index != 0) {
            Card temp = hand[0];
            hand[0] = hand[max_index];
            hand[max_index] = temp;
        }

        return true;
    } else {
        return false;
    }
}

bool HasThreeOfAKind(Hand hand) {
    int count[14] = {0};
    int three_value;

    for (int i = 0; i < 5; i++) {
        int order = Order(hand[i].face);
        count[order]++;
    }

    for (int i = 1; i < 14; i++) {
        if (count[i] == 4) {
            return false;
        }
    }

    int has_three_of_a_kind = 0;

    for (int i = 1; i < 14; i++) {
        if (count[i] == 3) {
            has_three_of_a_kind = 1;
            three_value = i;
            break;
        }
    }

    if (has_three_of_a_kind) {
        int max_index = 0;

        for (int i = 0; i < 5; i++) {
            if (Order(hand[i].face) == three_value) {
                if (BiggerThan(hand[i], hand[max_index])) {
                    max_index = i;
                }
            }
        }

        if (max_index != 0) {
            Card temp = hand[0];
            hand[0] = hand[max_index];
            hand[max_index] = temp;
        }

        return true;
    } else {
        return false;
    }
}

bool HasOnePair(Hand hand, bool exclude_a_card, Card excluded_card) {
    int count[14] = {0};
    int pair_value;
    bool found_pair = false;

    for (int i = 0; i < 5; i++) {
        if (exclude_a_card && hand[i].face == excluded_card.face && hand[i].suit == excluded_card.suit) {
            continue;
        }
        int order = Order(hand[i].face);
        count[order]++;
    }

    for (int i = 1; i < 14; i++) {
        if (count[i] >= 3) {
            return false;
        }
    }

    for (int i = 1; i < 14; i++) {
        if (count[i] == 2) {
            found_pair = true;
            pair_value = i;
            break;
        }
    }

    if (!found_pair) {
        return false;
    }

    int max_index = -1;

    for (int i = 0; i < 5; i++) {
        if(Order(hand[i].face) == pair_value) {
            if (max_index == -1 || BiggerThan(hand[i], hand[max_index])) {
                max_index = i;
            }
        }
    }

    if (max_index != 0 && max_index != -1) {
        Card temp = hand[0];
        hand[0] = hand[max_index];
        hand[max_index] = temp;
    }

    return true;
}

bool IsTwoPairs(Hand hand) {
    int count[14] = {0};
    int pair_values[2] = {0, 0};
    int pair_count = 0;

    for (int i = 0; i < 5; i++) {
        int order = Order(hand[i].face);
        count[order]++;
    }

    for (int i = 13; i >= 1; i--) {
        if (count[i] == 2) {
            pair_values[pair_count] = i;
            pair_count++;
            if (pair_count == 2) break;
        }
    }

    if (pair_count != 2) return false;

    int idx = 0;

    for (int pv = 0; pv < 2; pv++) {
        for (int i = 0; i < 5; i++) {
            if (Order(hand[i].face) == pair_values[pv]) {
                if (idx != i) {
                    Card temp = hand[idx];
                    hand[idx] = hand[i];
                    hand[i] = temp;
                }
                idx++;
            }
        }
    }

    for (int i = idx; i < 5; i++) {
        if (Order(hand[i].face) != pair_values[0] && Order(hand[i].face) != pair_values[1]) {
            if (i != 4) {
                Card temp = hand[i];
                hand[i] = hand[4];
                hand[4] = temp;
            }
            break;
        }
    }

    if (BiggerThan(hand[1], hand[0])) {
        Card temp = hand[0];
        hand[0] = hand[1];
        hand[1] = temp;
    }

    if (BiggerThan(hand[3], hand[2])) {
        Card temp = hand[2];
        hand[2] = hand[3];
        hand[3] = temp;
    }

    Card temp = hand[1];
    hand[1] = hand[2];
    hand[2] = temp;

    return true;
}

bool IsFullHouse(Hand hand) {   
    int count[14] = {0};
    int three_value = 0, two_value = 0;

    for (int i = 0; i < 5; i++) {
        int order = Order(hand[i].face);
        count[order]++;
    }

    for (int i = 1; i < 14; i++) {
        if (count[i] == 3) three_value = i;
        else if (count[i] == 2) two_value = i;
    }

    if (three_value && two_value) {
        int idx = 0;

        for (int i = 0; i < 5; i++) {
            if (Order(hand[i].face) == three_value) {
                if (idx != i) {
                    Card temp = hand[idx];
                    hand[idx] = hand[i];
                    hand[i] = temp;
                }
                idx++;
            }
        }
        for (int i = idx; i < 5; i++) {
            if (Order(hand[i].face) == two_value) {
                if (idx != i) {
                    Card temp = hand[idx];
                    hand[idx] = hand[i];
                    hand[i] = temp;
                }
                idx++;
            }
        }
        return true;
    }
    return false;
}

bool Zilch(Hand hand) {
    Card largest = FindLargest(hand);
    int max_index = 0;
    for (int i = 0; i < 5; i++) {
        if (hand[i].face == largest.face && hand[i].suit == largest.suit) {
            max_index = i;
            break;
        }
    }
    if (max_index != 0) {
        Card temp = hand[0];
        hand[0] = hand[max_index];
        hand[max_index] = temp;
    }
    return true;
}

int RankHand(Hand hand) {
    int rank = 0;
    if (IsStraightFlush(hand)) {
        rank = 8;
    } else if (IsFourOfAKind(hand)) {
        rank = 7;
    } else if (IsFullHouse(hand)) {
        rank = 6;
    } else if (IsFlush(hand)) {
        rank = 5;
    } else if (IsStraight(hand)) {
        rank = 4;
    } else if (HasThreeOfAKind(hand)) {
        rank = 3;
    } else if (IsTwoPairs(hand)) {
        rank = 2;
    } else if (HasOnePair(hand, false, hand[0])) {
        rank = 1;
    } else {
        Zilch(hand);
        rank = 0;
    }

    return rank;
}

void PrintRankUpper(int rank, char* output) {
    switch (rank) {
        case 8: sprintf(output, "Straight flush"); break;
        case 7: sprintf(output, "Four of a kind"); break;
        case 6: sprintf(output, "Full house"); break;
        case 5: sprintf(output, "Flush"); break;
        case 4: sprintf(output, "Straight"); break;
        case 3: sprintf(output, "Three of a kind"); break;
        case 2: sprintf(output, "Two pairs"); break;
        case 1: sprintf(output, "One pair"); break;
        default: sprintf(output, "Zilch"); break;
    }
}

void PrintRankLower(int rank, char* output) {
    switch (rank) {
        case 8: sprintf(output, "straight flush"); break;
        case 7: sprintf(output, "four of a kind"); break;
        case 6: sprintf(output, "full house"); break;
        case 5: sprintf(output, "flush"); break;
        case 4: sprintf(output, "straight"); break;
        case 3: sprintf(output, "three of a kind"); break;
        case 2: sprintf(output, "two pairs"); break;
        case 1: sprintf(output, "one pair"); break;
        default: sprintf(output, "zilch"); break;
    }
}

void DescriptionCard(Hand hand, char* output, int rank) {
    char temp1[20], temp2[20];

    if (rank == 2) {
        PrintCard(hand[0], temp1);
        PrintCard(hand[1], temp2);
        sprintf(output, "(%s and %s)", temp1, temp2);
    } else {
        PrintCard(hand[0], temp1);
        sprintf(output, "(%s)", temp1);
    }
}

int CompareSameRankHands(Hand hand1, Hand hand2, int rank) {
    switch (rank) {
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 1:
            {
                if (BiggerThan(hand1[0], hand2[0])) {
                    return 1;
                } else if (BiggerThan(hand2[0], hand1[0])) {
                    return -1;
                } else {
                    return 0;
                }
            }
        case 2:
                for (int i = 0; i < 2; i++) {
                    if (hand1[i].face > hand2[i].face) return 1;
                    if (hand1[i].face < hand2[i].face) return -1;
                }
                for (int i = 0; i < 2; i++) {
                    if (hand1[i].suit > hand2[i].suit) return 1;
                    if (hand1[i].suit < hand2[i].suit) return -1;
                }
                    return 0;
        case 0:
            {
                for (int i = 0; i < 5; i++) {
                    if (BiggerThan(hand1[i], hand2[i])) {
                        return 1;
                    } else if (BiggerThan(hand2[i], hand1[i])) {
                        return -1;
                    }
                }
                return 0;
            }
        return 0;
    }
}


void Play(Hand hand1, Hand hand2) {
    int rank1 = 0, rank2 = 0;
    char output1[50], output2[50];
    char desc1[50], desc2[50];

    rank1 = RankHand(hand1);
    rank2 = RankHand(hand2);

    PrintRankUpper(rank1, output1);
    PrintRankLower(rank2, output2);

    DescriptionCard(hand1, desc1, rank1);
    DescriptionCard(hand2, desc2, rank2);

    if (rank1 > rank2) {
        printf("%s %s wins over %s %s.", output1, desc1, output2, desc2);
    } else if (rank1 < rank2) {
        printf("%s %s loses to %s %s.", output1, desc1, output2, desc2);
    } else {
        int result = CompareSameRankHands(hand1, hand2, rank1);
        if (result > 0) {
            printf("%s %s wins over %s %s.", output1, desc1, output2, desc2);
        } else if (result < 0) {
            printf("%s %s loses to %s %s.", output1, desc1, output2, desc2);
        } else {
            printf("%s %s ties with %s %s.", output1, desc1, output2, desc2);
        }
    }
}

int main() {
    Hand hand1, hand2;

    if (InputHand(hand1) && InputHand(hand2)) {
        Play(hand1, hand2);
    }

    return 0;
}