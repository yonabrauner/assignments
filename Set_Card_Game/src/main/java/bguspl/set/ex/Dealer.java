package bguspl.set.ex;

import bguspl.set.Env;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentLinkedDeque;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import org.kie.api.runtime.KieSession.AtomicAction;

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
    private long reshuffleTime = 60000;
    private Thread[] playersThread;
    protected BlockingQueue<Integer> playersToCheck= new LinkedBlockingQueue<Integer>();

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
        createAndStartThreads();
        while (!shouldFinish()) {
            Collections.shuffle(deck);
            placeCardsOnTable();
            updateTimerDisplay(true);
            timerLoop();
            updateTimerDisplay(true);
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
            while(!playersToCheck.isEmpty()){
                try{
                    checkTokens(playersToCheck.take());
                }catch(InterruptedException e){}
            }
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
    }
    private void removeCardsFromTable(int player) {
        for (int token : table.tokens.get(player)){
                    table.removeCard(token);
        }
    }

    /**
     * Check if any cards can be removed from the deck and placed on the table.
     */
    private void placeCardsOnTable() {
        List<Integer> randomize = IntStream.rangeClosed(0, 11).boxed().collect(Collectors.toList());
        Collections.shuffle(randomize);
        for(int i : randomize)
            if (table.slotToCard[i] == null ){
                table.placeCard(deck.remove(0), i);
                try {
                    Thread.sleep(100);
                } catch (Exception e) {
                }
                if (deck.isEmpty())
                    return;
            }
        table.hints();
    }

    /**
     * Sleep for a fixed amount of time or until the thread is awakened for some purpose.
     */
    private void sleepUntilWokenOrTimeout() {
        // TODO implement
            try{
                if(reshuffleTime - System.currentTimeMillis() > 5000)
                 Thread.sleep(1000);
                else
                    Thread.sleep(10); 
            } catch(InterruptedException e){
                System.out.println("sleep intrrupted");
            }
            
        
    }

    /**
     * Reset and/or update the countdown and the countdown display.
     */
    private void updateTimerDisplay(boolean reset) {
        // TODO implement
        if (reset){
            reshuffleTime = System.currentTimeMillis()+ 15000;
        }
        env.ui.setCountdown(reshuffleTime - System.currentTimeMillis(), reshuffleTime - System.currentTimeMillis() < 5000);
    }

    /**
     * Returns all the cards from the table to the deck.
     */
    private void removeAllCardsFromTable() {
        // TODO implement
        for(int i = 0; i < 12; i++){
            deck.add(table.slotToCard[i]);
            table.removeCard(i);
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

    public synchronized void checkTokens(int player) throws InterruptedException{
            int[] set = table.getPlayerSet(player);
            if(set.length != 3){
                return;
            }
            if(env.util.testSet(set)){
                players[player].actions.add(-1);
                // env.ui.setScore(player, players[player].getScore());
                removeCardsFromTable(player);
                table.removeTokens(player);
                Collections.shuffle(deck);
                updateTimerDisplay(true);
                players[player].resetTokens();
                placeCardsOnTable();
            }
            else{
                players[player].actions.add(-2);

            }
            // players[player].notify();
            // playersThread[player].start();
    }

    private void createAndStartThreads(){
        playersThread = new Thread[players.length];
        for(int i=0; i < playersThread.length;i++){
            playersThread[i] = new Thread(players[i], Integer.toString(i));
            playersThread[i].start();
        }
    }

}

