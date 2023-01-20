#include "ELFLoader.hh"

namespace ELFLoader
{

    ELFFile::ELFFile(const std::string &filename, const Logging::LoggerPtr &logger) : logger(logger)
    {
        if (!reader.load(filename))
        {
            logger->error("Failed to load elf file: ", filename);
            exit(-1);
        }
    }

    sectionPtr ELFFile::get_symbol_table()
    {
        for (auto sec: reader.sections)
        {
            if (sec->get_name() == ".symtab") return sec;
        }

        logger->error("Can't get symbol table");
        exit(-1);
    }

    Addr ELFFile::get_symbol_by_name(const std::string &symbol_name)
    {
        const ELFIO::symbol_section_accessor symbol_access(reader, get_symbol_table());

        Addr address;
        ELFIO::Elf_Xword size;
        u_int8_t bind, type;
        ELFIO::Elf_Half section_index;
        u_int8_t other;

        bool has_symbol = symbol_access.get_symbol(symbol_name, address, size, bind, type, section_index, other);
        if (has_symbol) return address;

        logger->critical("Failed to get {} in symbol table", symbol_name.c_str());
        return 0;
    }

    Addr ELFFile::get_entry()
    {
        return get_symbol_by_name("_start");
    }

    Addr ELFFile::get_size()
    {
        return get_symbol_by_name("_end") - get_entry();
    }

    Addr ELFFile::get_fromhost()
    {
        return get_symbol_by_name("fromhost");
    }

    Addr ELFFile::get_tohost()
    {
        return get_symbol_by_name("tohost");
    }

    bool ELFFile::load_to(const Sim::Memory::BaseDramPtr &dram)
    {
        for (auto seg: reader.segments)
        {
            const size_t size = seg->get_file_size();
            const uint64_t addr = seg->get_physical_address();
            const u_char *data = (u_char *) seg->get_data();

            if (data != nullptr)
            {
                dram->write(data, addr, size);
            }
        }

        return true;
    }

}