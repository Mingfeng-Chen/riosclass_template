#pragma once

#include <string>
#include "memory/Memory.hh"

namespace ELFLoader
{
    typedef ELFIO::elfio Reader;
    typedef ELFIO::segment *segmentPtr;
    typedef ELFIO::section *sectionPtr;

    /**
     * @brief ELFFile wrapper class
     */
    class ELFFile
    {
    protected:
        /* ELFIO instance */
        Reader reader;

        Logging::LoggerPtr logger;

    public:
        /**
         * @brief Constructor
         *
         * @param filename name of ELF file to load
         */
        ELFFile(const std::string &filename, const Logging::LoggerPtr &logger);

        /**
         * @brief get symbol table
         * 
         * @return segmentPtr 
         */
        sectionPtr get_symbol_table();

        /**
         * @brief Get the symbol address by its name
         * 
         * @param symbol 
         * @return Addr 
         */
        Addr get_symbol_by_name(const std::string &symbol_name);

        /**
         * @brief Get the address of entry with symbol "_start"
         * 
         * @return Addr 
         */
        Addr get_entry();

        /**
         * @brief Get the size of elf file from symbol "_start" to "_end"
         * 
         * @return Addr 
         */
        Addr get_size();

        /**
         * @brief Get the address of fromhost with symbol "fromhost"
         * 
         * @return Addr 
         */
        Addr get_fromhost();

        /**
         * @brief Get the address of tohost with symbol "tohost"
         * 
         * @return Addr 
         */
        Addr get_tohost();

        /**
         * @brief Load elf file into memory
         * 
         * @param dram 
         * @return true 
         * @return false 
         */
        bool load_to(const Sim::Memory::BaseDramPtr &dram);
    };
}
