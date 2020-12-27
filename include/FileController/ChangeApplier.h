#pragma once

class ChangeApplier {
public:
    ChangeApplier(const Change &ch, std::shared_ptr<FileStorage> file);
    ~ChangeApplier() = default;
    bool applyChange();
    Change getChange() const;
    FileStorage getFile();
    Change ch_{};
    std::shared_ptr<FileStorage> file_;
};
