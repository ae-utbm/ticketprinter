import './index.css';
import './Button.css';

interface buttonOptions {
	text?: string;
	icon?: string;
	disabled?: boolean;
	onClick?: () => void;
	className?: string;
}

export default function Button(props: buttonOptions) {
	const { text, icon, disabled, onClick, className } = props;

	const classes = `${icon ? 'icon' : ''} ${
		text === undefined ? 'no-text' : ''
	} ${className}`;

	return (
		<button
			onClick={onClick}
			type="button"
			className={classes}
			disabled={disabled}
		>
			{icon && <img src={icon} alt="icon" />}
			{text && <span>{text}</span>}
		</button>
	);
}

Button.defaultProps = {
	text: undefined,
	icon: undefined,
	disabled: false,
	onClick: undefined,
	className: '',
};
