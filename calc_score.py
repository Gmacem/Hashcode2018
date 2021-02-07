import subprocess

if __name__ == "__main__":
    for filename in ["a_example.in", "b_should_be_easy.in", "c_no_hurry.in", "d_metropolis.in", "e_high_bonus.in"]:
        args = ("./solve", "<", filename)
        popen = subprocess.Popen(args, stdout=subprocess.PIPE)
        popen.wait()
        output = popen.stdout.read().decode()
        print("Filename:", filename)
        print(output)
