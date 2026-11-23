#include <iostream>
#include "app/Application.h"

void Application::initialize()
{
    std::cout << "Initializing Micromouse Simulator...\n";
    m_simulator.setupSampleMaze();
}

void Application::run()
{
    while (true)
    {
        std::cout << "\n--- MENU MO PHONG MICROMOUSE (16x16) ---\n";
        std::cout << "  1. Chay thuat toan BFS\n";
        std::cout << "  2. Chay thuat toan DFS\n";
        std::cout << "  3. Chay thuat toan Flood Fill\n";
        std::cout << "  0. Thoat chuong trinh\n";
        std::cout << "Nhap lua chon: ";

        int choice = 0;
        if (!(std::cin >> choice) || choice == 0)
            break;

        if (choice == 1)      m_simulator.runSimulation(AlgorithmType::BFS);
        else if (choice == 2) m_simulator.runSimulation(AlgorithmType::DFS);
        else if (choice == 3) m_simulator.runSimulation(AlgorithmType::FLOOD_FILL);
        else                  std::cout << "Lua chon khong hop le!\n";
    }
}

void Application::shutdown()
{
    std::cout << "Shutting down application.\n";
}