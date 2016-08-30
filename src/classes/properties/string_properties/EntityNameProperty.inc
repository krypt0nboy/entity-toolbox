<?php

/**
 * Class EntityNameProperty
 */
class EntityNameProperty extends VarcharProperty {
  /** {{@inheritdoc}} */
  public function __construct() {
    parent::__construct();
    $this->type                = 'name';
    $this->defaultLabel        = '%label% name';
    $this->defaultDescription  = 'The %label% human-readable name.';
    $this->defaultKey          = 'label';
    $this->defaultHasRevisions = TRUE;
  }

  /** {{@inheritdoc}} */
  protected function setBaseSchemaParams(array $params = array()) {
    $params += array(
      'description' => 'The name of the %toolbox_info_entity_type% - a human-readable identifier.'
    );
    parent::setBaseSchemaParams($params);
  }

  /** {{@inheritdoc}} */
  protected function setEditFormParams(array $params = array()) {
    $params += array('required' => TRUE);
    parent::setEditFormParams($params);
  }
}