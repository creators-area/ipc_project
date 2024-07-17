# include "ipc.h"


int	recursive_power(int nb, int power)
{
	int	res;

	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else
	{
		res = nb * recursive_power(nb, power - 1);
		return (res);
	}
}

char	*letter_to_string(char const *string, char const letter)
{
	int		i;
	int		j;
	char	*temp;
	
	i = 0;
	j = 0;
	
	temp = malloc((strlen(string) + 2) * sizeof(char));
	if (!temp)
		return (NULL);
	while (string[i])
		temp[j++] = string[i++];
	i = 0;
	temp[j++] = letter;
	temp[j] = 0;
	free ((void *)(string));
	return (temp);

}

void signal_handler(int signum)
{
    static int	bits_counter = 0;
	static int	char_result = 0;
	static int	str_len = 0;
	static char	*final;
	
	if (!final)
		final = strdup("");
	
	if (signum == SIGUSR1)
		char_result = char_result + 0;
	else if (signum == SIGUSR2)
		char_result = char_result + (1 * recursive_power(2, 7 - bits_counter));
	bits_counter++;
	if (bits_counter == 8)
	{
		final = letter_to_string(final, char_result);
		if (char_result == '\0')
		{
			printf("%s\n", final);
			final = NULL;
		}
		bits_counter = 0;
		char_result = 0;
		str_len += 1;
	}
}

int main(void)
{
    struct sigaction action;

    printf("Welcome to the Creators Area Server\n");
    printf("PID: %d\n", getpid());

    action.sa_handler = signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    while (1)
		pause();

    return 0;
}
