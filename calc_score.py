import subprocess

if __name__ == "__main__":
    for filename in ["a_example.in", "b_should_be_easy.in", "c_no_hurry.in", "d_metropolis.in", "e_high_bonus.in"]:
        cat = subprocess.Popen(('cat', "tests/" + filename), stdout=subprocess.PIPE)
        output = subprocess.check_output(("./solve"), stdin=cat.stdout).decode()
        cat.wait()
        print("Filename:", filename)
        print(output)
