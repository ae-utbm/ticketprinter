import './index.css';
import './Button.css';

interface buttonOptions {
  text: string;
  icon?: string;
  disabled?: boolean;
}

export default function Button(props: buttonOptions) {
  const { text, icon, disabled } = props;

  if (icon) {
    return (
      <button type="button" className="icon" disabled={disabled}>
        <img src={icon} alt="" />
        <span>{text}</span>
      </button>
    );
  }

  return (
    <button type="button" disabled={disabled}>
      <span>{text}</span>
    </button>
  );
}

Button.defaultProps = {
  icon: undefined,
  disabled: false,
};
