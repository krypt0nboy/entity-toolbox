<?php

/**
 * Class EntityPropertyInfoPropertyModel
 */
class EntityPropertyInfoReferenceMultipleNumericPropertyModel extends EntityPropertyInfoReferenceNumericPropertyModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'label'               => array(
            'default' => '%reference_property_info_label% IDs',
          ),
          'description'         => array(
            'default' => 'The entity %reference_property_info_label% IDs.',
          ),
          'type'                => array(
            'default' => 'list<integer>',
          ),
          'bundle'              => array(
            'default' => NULL,
          ),
          'options list'        => array(
            'method' => 'buildOptionsList',
          ),
          'getter callback'     => array(
            'default' => '%reference_property_info_callbacks_getter%',
          ),
          'setter callback'     => array(
            'default' => '%reference_property_info_callbacks_setter%',
          ),
          'validation callback' => array(
            'default' => '%reference_property_info_callbacks_validation%',
          ),
          'access callback'     => array(
            'default' => '%reference_property_info_callbacks_access%',
          ),
          'setter permission'   => array(
            'default' => '%reference_property_info_callbacks_setter_permission%',
          ),
          'schema field'        => array(
            'default' => NULL,
          ),
          'required'            => array(
            'default' => '%reference_property_info_required%',
          ),
          'property info'       => array(
            'method' => 'buildPropertyInfo',
          ),
          'property info alter' => array(
            'method' => 'buildPropertyInfoAlter',
          ),
          'auto creation'       => array(
            'method' => 'buildAutoCreation',
          ),
          'translatable'        => array(
            'default' => '%reference_property_info_has_translations%',
          ),
          'entity token'        => array(
            'method' => 'buildToken',
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}