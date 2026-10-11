#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

namespace back::biological_debris
{
    // A "biological debris" is a plain text file holding the body of a
    // progtein or a gene (no PROGTEIN/GENE header, no END: they are added
    // when the debris is inserted into a cell).
    struct Debris
    {
        std::string name;   // file name without extension
        std::string body;   // raw file content
    };

    inline fs::path debris_path = fs::path("/home") / "adrien" / "Programmation" /
        "Projets" / "BioEvo" / "data" / "experiments" / "biological_debris";
    inline fs::path progteins_debris_path = debris_path / "progteins";
    inline fs::path dna_debris_path       = debris_path / "DNA";

    inline std::vector<Debris> load_all(const fs::path& dir = debris_path)
    {
        std::vector<Debris> out;
        std::error_code ec;
        if (!fs::is_directory(dir, ec))
        {
            std::cerr << "Biological debris: directory not found: " << dir << "\n";
            return out;
        }

        for (const auto& entry : fs::directory_iterator(dir, ec))
        {
            if (!entry.is_regular_file())
                continue;

            std::ifstream file(entry.path());
            if (!file.is_open())
            {
                std::cerr << "Biological debris: could not open " << entry.path() << "\n";
                continue;
            }

            std::stringstream ss;
            ss << file.rdbuf();

            Debris d;
            d.name = entry.path().stem().string();
            d.body = ss.str();
            // strip trailing newlines / spaces
            while (!d.body.empty() && std::isspace((unsigned char)d.body.back()))
                d.body.pop_back();
            out.push_back(std::move(d));
        }

        std::sort(out.begin(), out.end(),
            [](const Debris& a, const Debris& b) { return a.name < b.name; });
        return out;
    }

    // Indent every line of `body` by `indent`.
    inline std::string indent_body(const std::string& body, const std::string& indent)
    {
        std::istringstream ss(body);
        std::string line, out;
        while (std::getline(ss, line))
        {
            size_t f = line.find_first_not_of(" \t");
            out += indent;
            out += (f != std::string::npos) ? line.substr(f) : std::string{};
            out += '\n';
        }
        return out;
    }

    // First whitespace-delimited token of a line, uppercased.
    inline std::string keyword_of(const std::string& line)
    {
        std::string kw;
        std::istringstream ls(line);
        ls >> kw;
        for (auto& c : kw) c = (char)std::toupper((unsigned char)c);
        return kw;
    }

    // Insert a PROGTEIN block just before the top-level DNA section
    // (or at the end of the text if there is none).
    inline std::string insert_progtein(const std::string& evox,
                                       const std::string& name,
                                       int id,
                                       const std::string& body)
    {
        std::string block = "PROGTEIN " + name + " id=" + std::to_string(id) + "\n"
                          + indent_body(body, "    ")
                          + "END\n\n";

        std::istringstream ss(evox);
        std::string line;
        size_t pos = 0;
        int depth = 0;
        while (std::getline(ss, line))
        {
            std::string kw = keyword_of(line);
            if (depth == 0 && kw == "DNA")
                return evox.substr(0, pos) + block + evox.substr(pos);
            if (kw == "END")       depth = std::max(0, depth - 1);
            else if (depth == 0 && !kw.empty() && kw[0] != '#') depth++;   // RAW, PROGTEIN, TRAIL...
            pos += line.size() + 1;
        }

        std::string out = evox;
        if (!out.empty() && out.back() != '\n') out += '\n';
        return out + "\n" + block;
    }

    // Insert a GENE block at the end of the DNA section
    // (creating the DNA section if there is none).
    inline std::string insert_gene(const std::string& evox,
                                   int id,
                                   const std::string& body)
    {
        std::string block = "    GENE id=" + std::to_string(id) + "\n"
                          + indent_body(body, "        ")
                          + "    END\n";

        std::istringstream ss(evox);
        std::string line;
        size_t pos = 0;
        int depth = 0;
        bool in_dna = false;
        while (std::getline(ss, line))
        {
            std::string kw = keyword_of(line);
            if (kw == "END")
            {
                if (in_dna && depth == 1)   // closing END of the DNA section
                    return evox.substr(0, pos) + block + evox.substr(pos);
                depth = std::max(0, depth - 1);
            }
            else if (depth == 0 && !kw.empty() && kw[0] != '#')
            {
                in_dna = (kw == "DNA");
                depth++;
            }
            else if (in_dna && kw == "GENE")
            {
                depth++;
            }
            pos += line.size() + 1;
        }

        std::string out = evox;
        if (!out.empty() && out.back() != '\n') out += '\n';
        return out + "\nDNA\n" + block + "END\n";
    }

} // namespace back::biological_debris
