from __future__ import division
import os.path
from glob import glob
import json


class Progress:
    def __init__(self, project_name):
        self.project_name = project_name
        self.project_path = os.path.split(os.path.dirname(__file__))[0] + "/" + project_name + "/srcs/"
        self.sources_found = [os.path.split(source)[1] for source in
                              glob(self.project_path + "/ft_*.c")]
        self.mains_found = [os.path.split(source)[1].replace("main_", "") for source in glob(
            os.path.dirname(os.path.abspath(__file__)) + "/" + project_name + "_mains/main_ft_*.c")]
        with open(os.path.dirname(os.path.abspath(__file__)) + "/tools/asked_" + project_name + ".json",
                  "r") as to_do_list:
            self.to_do = json.load(to_do_list)

    def part1_realized(self):
        return set(self.sources_found) & set(self.to_do["part1"])

    def part1_required(self):
        return set(self.to_do["part1"])

    def part2_realized(self):
        return set(self.sources_found) & set(self.to_do["part2"])

    def part2_required(self):
        return set(self.to_do["part2"])

    def bonus_realized(self):
        return set(self.sources_found) & set(self.to_do["bonus"])

    def bonus_required(self):
        return set(self.to_do["bonus"])

    def total_required(self):
        return set(list(self.part1_required()) + list(self.part2_required()) + list(self.bonus_required()))

    def total_realized(self):
        return set(list(self.part1_realized()) + list(self.part2_realized()) + list(self.bonus_realized()))

    def overview(self):
        return {
            "part1": (len(self.part1_realized()), len(self.part1_required())),
            "part2": (len(self.part2_realized()), len(self.part2_required())),
            "bonus": (len(self.bonus_realized()), len(self.bonus_required())),
            "total": (len(self.total_realized()), len(self.total_required())),
            "extra": len(self.extra_realized())
        }

    def __repr__(self):
        part1 = "part1\t\t\t{}\t/ {}\t\t{:.0%}\n".format(self.overview()["part1"][0],
                                                         self.overview()["part1"][1],
                                                         self.overview()["part1"][0] /
                                                         self.overview()["part1"][1])
        part2 = "part2\t\t\t{}\t/ {}\t\t{:.0%}\n".format(self.overview()["part2"][0],
                                                         self.overview()["part2"][1],
                                                         self.overview()["part2"][0] /
                                                         self.overview()["part2"][1])
        bonus = "bonus\t\t\t{}\t/ {}\t\t\t{:.0%}\n".format(self.overview()["bonus"][0], self.overview()["bonus"][1],
                                                           self.overview()["bonus"][0] / self.overview()["bonus"][1])
        total = "total\t\t\t{}\t/ {}\t\t{:.0%}\n".format(self.overview()["total"][0], self.overview()["total"][1],
                                                         self.overview()["total"][0] / self.overview()["total"][1])
        extra = "extra\t\t\t+{}".format(self.overview()["extra"])
        sep = "-" * 70 + "\n"
        title = "part\t\t\tdo\t/ on\t\t %\n"
        return "\n" + title + sep + part1 + part2 + bonus + sep + total + extra

    def full_coverage(self):
        if len(set(self.sources_found) - set(self.mains_found)) == 0:
            return True
        else:
            return False

    def extra_realized(self):
        to_do = self.to_do["part1"] + self.to_do["part2"] + self.to_do["bonus"]
        return set(self.sources_found) - set(to_do)


if __name__ == "__main__":
    libft = Progress("libft")
    print libft
    print ""
    for ft in libft.part1_required() - libft.part1_realized():
        print ft
    print ""
    for ft in libft.part2_required() - libft.part2_realized():
        print ft
    print ""
    for ft in libft.bonus_required() - libft.bonus_realized():
        print ft