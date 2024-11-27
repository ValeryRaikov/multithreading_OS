import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(2);

        Runnable displaySymbol1 = () -> displaySymbol(1, 'X');
        Runnable displaySymbol2 = () -> displaySymbol(2, 'O');

        executor.submit(displaySymbol1);
        executor.submit(displaySymbol2);

        executor.shutdown();
    }

    private static void displaySymbol(int threadId, char symbol) {
        for (int i = 0; i < 100; i++) {
            System.out.println("Thread " + threadId + " -> " + symbol);
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Thread " + threadId + " interrupted.");
            }
        }
    }
}