import subprocess
import matplotlib.pyplot as plt

# Function to run the C program and collect data
def run_sort_tests(array_sizes):
    results = {"Bubble Sort": [], "Quick Sort": [], "Merge Sort": [], "Heap Sort": []}

    for n in array_sizes:
        process = subprocess.Popen(["./sort_performance", str(n)], stdout=subprocess.PIPE)
        output, _ = process.communicate()
        lines = output.decode("utf-8").strip().split("\n")

        for line in lines:
            algo, size, time = line.split(",")
            results[algo].append((int(size), float(time)))
        print("Finished array size: " + str(n))

    return results


def plot_results(results):
    plt.figure()
    for algo, data in results.items():
        sizes, times = zip(*data)
        plt.plot(sizes, times, label=algo)

    plt.xlabel("Array Size")
    plt.ylabel("Time (s)")
    plt.yscale("log")  # Set the y-axis to a logarithmic scale
    plt.title("Sorting Algorithm Performance (Log Scale)")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    array_sizes = [10 * n for n in range(10, 5000, 25)]
    #array_sizes = range(1000, 
    #array_sizes = [100, 500, 1000, 5000, 10000, 20000]
    results = run_sort_tests(array_sizes)
    plot_results(results)

