#ifndef _GPIO_KEYS_H
#define _GPIO_KEYS_H
extern struct class *sec_class;

struct device;

struct gpio_keys_button {
	/* Configuration parameters */
	unsigned int code;	/* input event code (KEY_*, SW_*) */
	int gpio;		/* -1 if this key does not support gpio */
	int active_low;
	const char *desc;
	unsigned int type;	/* input event type (EV_KEY, EV_SW, EV_ABS) */
	int wakeup;		/* configure the button as a wake-up source */
	int debounce_interval;	/* debounce ticks interval in msecs */
	bool can_disable;
	int value;		/* axis value for EV_ABS */
	unsigned int irq;	/* Irq number in case of interrupt keys */
};

struct gpio_keys_platform_data {
	struct gpio_keys_button *buttons;
	int nbuttons;
	unsigned int poll_interval;	/* polling interval in msecs -
					   for polling driver only */
	unsigned int rep:1;		/* enable input subsystem auto repeat */
	int (*enable)(struct device *dev);
	void (*disable)(struct device *dev);
	const char *name;		/* input device name */
#ifdef CONFIG_SENSORS_HALL
	int gpio_flip_cover;
	int flip_code;

#endif
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	bool workaround_set;
#endif
#ifdef CONFIG_SENSORS_HALL_DEBOUNCE
	bool debounce_set;
#endif
};
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
extern void gpio_hall_irq_set(int state, bool auth_changed);
enum state {
	disable = 0,
	enable
};
#endif

#endif
