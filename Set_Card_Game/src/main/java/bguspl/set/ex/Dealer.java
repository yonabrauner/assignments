package bguspl.set.ex;

import bguspl.set.Env;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * This class manages the dealer's threads and data
 */
public class Dealer implements Runnable {

    /**
     * The game environment object.
     */
    private final Env env;

    /**
     * Game entities.
     */
    private final Table table;
    private final Player[] players;

    /**
     * The list of card ids that are left in the dealer's deck.
     */
    private final List<Integer> deck;

    /**
     * True iff game should be terminated due to an external event.
     */
    private volatile boolean terminate;

    /**
     * The time when the dealer needs to reshuffle the deck due to turn timeout.
     */
    private long reshuffleTime = Long.MAX_VALUE;
    private Thread[] playersThread;

    public Dealer(Env env, Table table, Player[] players) {
        this.env = env;
        this.table = table;
        this.players = players;
        deck = IntStream.range(0, env.config.deckSize).boxed().collect(Collectors.toList());
    }

    /**
     * The dealer thread starts here (main loop for the dealer thread).
     */
    @Override
    public void run() {
        System.out.printf("Info: Thread %s starting.%n", Thread.currentThread().getName());
        while (!shouldFinish()) {
            createAndStartThreads();
            Collections.shuffle(deck);
            placeCardsOnTable();
            timerLoop();
            updateTimerDisplay(false);
            removeAllCardsFromTable();
            
        }
        announceWinners();
        System.out.printf("Info: Thread %s terminated.%n", Thread.currentThread().getName());
    }

    /**
     * The inner loop of the dealer thread that runs as long as the countdown did not time out.
     */
    private void timerLoop() {
        while (!terminate && System.currentTimeMillis() < reshuffleTime) {
            sleepUntilWokenOrTimeout();
            updateTimerDisplay(false);
            removeCardsFromTable();
            placeCardsOnTable();
        }
    }

    /**
     * Called when the game should be terminated due to an external event.
     */
    public void terminate() {
        // TODO implement
        
    }

    /**
     * Check if the game should be terminated or the game end conditions are met.
     *
     * @return true iff the game should be finished.
     */
    private boolean shouldFinish() {
        return terminate || env.util.findSets(deck, 1).size() == 0;
    }

    /**
     * Checks if any cards should be removed from the table and returns them.
     */
    private void removeCardsFromTable() {
        // TODO implement
        for(List<Integer> tokens : table.tokens){
            if(tokens.size()==3){
                for(Integer slot : tokens){
                    table.removeCard(slot);
                }
            }
        }
    }

    /**
     * Check if any cards can be removed from the deck and placed on the table.
     */
    private void placeCardsOnTable() {
        // TODO implement
        for(int i = 0; i < 12; i++){
            if (table.slotToCard[i] == null){
                table.placeCard(deck.remove(0), i);
                if (deck.isEmpty())
                    return;
            }
        }

   
    }

    /**
     * Sleep for a fixed amount of time or until the thread is awakened for some purpose.
     */
    private void sleepUntilWokenOrTimeout() {
        // TODO implement
    }

    /**
     * Reset and/or update the countdown and the countdown display.
     */
    private void updateTimerDisplay(boolean reset) {
        // TODO implement
    }

    /**
     * Returns all the cards from the table to the deck.
     */
    private void removeAllCardsFromTable() {
        // TODO implement
        for (Integer card: table.slotToCard){
            deck.add(card);
            table.removeCard(card);
        }
    }

    /**
     * Check who is/are the winner/s and displays them.
     */
    private void announceWinners() {
        // TODO implement
        List<Integer> winners = new LinkedList<Integer>();
        int maxPoints = 0;
        for(Player p : players){
            int playerPoints = p.getScore();
            if(playerPoints > maxPoints){
                winners.clear();
                winners.add(p.id);
            }
            if(playerPoints == maxPoints)
                winners.add(p.id);
        }
        env.ui.announceWinner(winners.stream().mapToInt(i->i).toArray());
    }

    public void checkTokens(int player){
        int[] set = table.getPlayerSet(player);
        if(env.util.testSet(set)){
            players[player].point();
            env.ui.setScore(player, players[player].getScore());
            removeCardsFromTable();
            Collections.shuffle(deck);
        }
        else{
            table.tokens.get(player).clear();
            players[player].penalty();
        }
            
    }

    private void createAndStartThreads(){
        playersThread = new Thread[players.length];
        for(int i=0; i < playersThread.length;i++){
            playersThread[i] = new Thread(players[i]);
            playersThread[i].start();
        }
    }

}
