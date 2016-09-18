<?php

/**
 * Class EntityToolboxInfoPropertyFormsFormModel
 */
class EntityToolboxInfoPropertyFormsFormModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'expose'   => array(
            'type'    => 'boolean',
            'default' => '%property_default_forms_edit_expose%',
          ),
          'widget'   => array(
            'type'    => 'string',
            'default' => '%property_default_forms_edit_widget%',
          ),
          'required' => array(
            'type'    => 'boolean',
            'method'  => '',
            'default' => '',
            'model'   => '',
          ),
          'rows'     => array(
            'type'    => 'integer',
            'method'  => '',
            'default' => '',
            'model'   => '',
          ),
          'weight'   => array(
            'type'    => 'integer',
            'method'  => '',
            'default' => '',
            'model'   => '',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}