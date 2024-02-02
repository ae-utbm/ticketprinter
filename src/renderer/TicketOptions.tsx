import { useState, ChangeEvent } from 'react';
import { ReactPhotoEditor } from 'react-photo-editor';

import Button from './Button';
import iconEdit from '../../assets/edit.svg';

import './index.css';
import './TicketOptions.css';
import 'react-photo-editor/dist/style.css';

export default function TicketOptions() {
	const [file, setFile] = useState<File | undefined>(undefined);
	const [showModal, setShowModal] = useState<boolean>(false);
	const [ticketUrl, setTicketUrl] = useState<string | undefined>(undefined);

	const setFileData = (e: ChangeEvent<HTMLInputElement>) => {
		const { files } = e.target;

		if (files && files.length > 0) {
			setFile(files[0]);
			setTicketUrl(URL.createObjectURL(files[0]));
		}
	};

	// Hide modal
	const hideModal = () => {
		setShowModal(false);
	};

	// Show modal if file is selected
	const showModalHandler = () => {
		if (file) {
			setShowModal(true);
		}
	};

	const handleSaveImage = (
		editedFile: React.SetStateAction<File | undefined>,
	) => {
		setFile(editedFile);
		setShowModal(false);
		setTicketUrl(URL.createObjectURL(editedFile as Blob));
	};

	return (
		<div className="ticket-options">
			<ReactPhotoEditor
				open={showModal}
				onClose={hideModal}
				file={file}
				onSaveImage={handleSaveImage}
				downloadOnSave
			/>

			<input
				type="file"
				onChange={(e) => setFileData(e)}
				multiple={false}
				accept="image/png, image/jpeg, image/jpg, image/webp"
			/>

			<div className="ticket-preview">
				{ticketUrl && (
					<>
						<img src={ticketUrl} alt="ticket" />
						<Button
							className="btn"
							icon={iconEdit}
							onClick={showModalHandler}
						/>
					</>
				)}
				{!ticketUrl && <p>Aucune étiquette</p>}
			</div>
		</div>
	);
}
