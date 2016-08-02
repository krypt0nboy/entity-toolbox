<?php

/**
 * @file
 *
 * This file contains the default EntityInlineEntityFormController for entities managed by entity_toolbox.
 */

/**
 * Class EntityToolboxInlineEntityFormController
 */
class EntityToolboxInlineEntityFormController extends EntityInlineEntityFormController {

  /**
   * {@inheritdoc}
   */
  public function entityForm($entity_form, &$form_state) {
	$entity = $entity_form['#entity'];
	properties_attach_form($this->entityType, $entity, $entity_form, $form_state);
	field_attach_form($this->entityType, $entity, $entity_form, $form_state);

	return $entity_form;
  }

  /**
   * {@inheritdoc}
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
	parent::entityFormSubmit($entity_form, $form_state);
  }
}