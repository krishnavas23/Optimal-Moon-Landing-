# 🌙 Optimal Moon Landing

> A C++ based lunar mission planning system that identifies the optimal habitat site, mining site, and shortest feasible power cable route using terrain analysis and pathfinding algorithms.

---

## 📖 Overview

Choosing the right location for a lunar base is a complex optimization problem. A suitable habitat requires **high solar illumination** for continuous power generation, while a mining site should have **high water-ice availability** for future resource extraction. Since these locations are often far apart, an efficient and safe route between them is equally important.

This project analyzes multiple lunar datasets and recommends:

- 🏠 Best Habitat Location
- ⛏️ Best Mining Location
- ⚡ Shortest feasible power cable route between them

The solution combines statistical analysis with graph algorithms to balance resource availability, terrain smoothness, and travel distance.

---

## 🚀 Features

- Read and process multiple lunar terrain datasets
- Analyze elevation, illumination, and water-ice probability maps
- Calculate terrain roughness using statistical methods
- Select top habitat and mining candidates
- Find shortest traversable path using **A\*** Pathfinding
- Generate final optimized mission plan
- Export results to text files

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts:** Data Structures & Algorithms
- **Algorithms:** A* Search, Prefix Sum, Sliding Window, Sorting
- **Data Format:** CSV Files

---

## 📂 Project Structure

```
Optimal-Moon-Landing
│
├── main.cpp
├── step1_csv.hpp
├── step2_stats.hpp
├── step3_pathfinding.hpp
├── step4_result.hpp
│
├── elevation.csv
├── illumination.csv
├── water_ice.csv
├── signal_occultation.csv
│
├── candidates.txt
├── result.txt
└── README.md
```

---

## ⚙️ How It Works

The project follows four major stages:

### 1️⃣ Data Loading

- Reads lunar datasets from CSV files.
- Validates and stores terrain information.

### 2️⃣ Terrain Analysis

Calculates:

- Average Illumination
- Water-Ice Probability
- Terrain Roughness (Standard Deviation)

using **2D Prefix Sum** for efficient computation.

### 3️⃣ Candidate Selection

Ranks potential habitat and mining locations based on:

- High illumination
- High water-ice probability
- Smooth terrain

The search space is reduced using clustering techniques.

### 4️⃣ Route Optimization

Uses the **A\*** Search Algorithm to find the shortest valid path between habitat and mining sites while respecting terrain slope constraints.

Finally, the highest scoring pair is selected.

---

## 🧠 Algorithms Used

| Algorithm | Purpose |
|------------|---------|
| Prefix Sum | Fast 5×5 statistical calculations |
| Sliding Window | Analyze local terrain |
| Sorting | Rank candidate locations |
| Spatial Clustering | Remove nearby duplicate candidates |
| A* Search | Shortest feasible path |
| Branch & Bound | Reduce unnecessary computations |

---

## 📊 Scoring Formula

The final score is calculated as:

```
Score =
0.5 × Habitat Illumination
+ 0.5 × Water-Ice Probability
− 0.001 × Path Length
```

The objective is to maximize resource availability while minimizing travel distance.

---

## 📥 Input Files

The program requires the following datasets:

- `elevation.csv`
- `illumination.csv`
- `water_ice.csv`
- `signal_occultation.csv`

Each dataset represents a **500 × 500** lunar terrain grid.

---

## 📤 Output

The project generates:

### `candidates.txt`

Contains the top-ranked habitat and mining candidates.

### `result.txt`

Displays:

- Best Habitat Coordinates
- Best Mining Coordinates
- Combined Score
- Terrain Roughness
- Path Length

---

## ▶️ How to Run

### Compile

```bash
g++ -std=c++17 main.cpp -o moon
```

### Execute

```bash
./moon
```

---

## 💡 Challenges Faced

- Processing large 500×500 terrain datasets efficiently
- Selecting the best locations from thousands of candidates
- Balancing multiple optimization objectives
- Finding feasible paths while considering elevation constraints
- Reducing computation time without sacrificing solution quality

---

## 📚 What I Learned

Through this project, I gained practical experience with:

- Advanced C++ programming
- File handling and CSV parsing
- Prefix Sum optimization
- Graph Algorithms
- A* Pathfinding
- Terrain analysis
- Multi-objective optimization
- Algorithm design and complexity analysis
- Real-world problem solving

---

## 🔮 Future Improvements

- Interactive graphical visualization
- 3D lunar terrain rendering
- Dynamic weight adjustment
- Parallel pathfinding
- Machine Learning based site selection
- Communication signal optimization
- Export optimal path coordinates

---

## 👨‍💻 Author

**Krishna Vashisht**

B.Tech Computer Science Engineering

GitHub: https://github.com/krishnavas23

LinkedIn: https://www.linkedin.com/in/krishna-vashisht-70877a306/

---

## ⭐ If you found this project interesting, consider giving it a Star!
