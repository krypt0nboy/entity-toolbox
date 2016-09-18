<?php

/**
 * Class EntityPropertyInfoPropertyModel
 */
class EntityPropertyInfoReferenceNumericPropertyModel extends EntityPropertyInfoPropertyModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'label'               => array(
            'default' => '%reference_info_label% ID',
          ),
          'description'         => array(
            'default' => 'The entity %reference_info_label% ID.',
          ),
          'type'                => array(
            'default' => 'integer',
          ),
          'bundle'              => array(
            'default' => NULL,
          ),
          'options list'        => array(
            'method' => 'buildOptionsList',
          ),
          'getter callback'     => array(
            'default' => '%property_callbacks_getter%',
          ),
          'setter callback'     => array(
            'default' => '%property_callbacks_setter%',
          ),
          'validation callback' => array(
            'default' => '%property_callbacks_validation%',
          ),
          'access callback'     => array(
            'default' => '%property_callbacks_access%',
          ),
          'setter permission'   => array(
            'default' => '%property_setter_permission%',
          ),
          'schema field'        => array(
            'method'  => NULL,
            'default' => '%property_schemas_fields_name_base%',
          ),
          'required'            => array(
            'default' => '%property_required%',
          ),
          'field'               => array(
            'method'  => NULL,
            'default' => FALSE,
          ),
          'computed'            => array(
            'method'  => NULL,
            'default' => TRUE,
          ),
          'entity views field'  => array(
            'default' => '%reference_property_info_views_expose%',
          ),
          'sanitize'            => array(
            'method' => 'buildSanitize',
          ),
          'raw getter callback' => array(
            'method' => 'buildRawGetterCallback',
          ),
          'clear'               => array(
            'method' => 'buildClear',
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